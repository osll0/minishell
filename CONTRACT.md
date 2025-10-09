# Minishell Exec 연동 계약서 (팀 핸드오프 가이드)

본 문서는 현재 구현된 exec/env/builtin/FD 유틸과, 앞으로 팀원이 구현할 렉서/파서/확장/heredoc/인터랙티브 루프가 자연스럽게 맞물리도록 하기 위한 계약(Contract)입니다. 파트 간 경계, 기대되는 입력/출력, 에러/시그널/상태코드 정책, 그리고 흔한 함정과 예시를 정리했습니다.

## 범위 요약 (현재 구현됨)
- Exec 코어: `execute_ast`, 단일/파이프 실행, 마지막 프로세스 종료코드 반영, 자식 내장 실행, PATH 해석, 리다이렉션(`< > >>`, heredoc FD 소비).
- Env/내장: 연결 리스트 env, 배열 변환; 자식 내장 `echo/pwd/env`, 부모 내장 `cd/export/unset/exit`.
- FD 유틸: 안전 래퍼(`open/dup2/close/pipe`), 파이프 배열 정리 버그 수정.
- 에러 출력 통일: exec는 `ex_print_err`/`ex_report_exec`, 내장은 `bi_print_err` 사용(“minishell: …” 톤).
- 시그널(자식): 자식에서 `SIGINT/SIGQUIT` 기본 동작(`ex_sig_child_default`).
- 테스트: resolve/exec/pipeline/builtin/signal 스모크 테스트 추가.

## Exec 연동 인터페이스
- 진입점: `int execute_ast(const t_ast *ast, t_env **penv);`
  - 입력: 파서가 만든 AST
  - 출력: 최종 종료 코드(마지막 프로세스 기준, bash 호환)
  - env: 부모 내장 `cd/export/unset/exit`는 `*penv`를 수정. 자식 내장/외부 명령은 부모 env에 영향 없음.

### AST 규약
- 노드 타입
  - `N_CMD`: `t_cmd{argv, argc, redirs, n_redirs}` 모두 채워서 전달 (NULL-terminated argv)
  - `N_PIPE`: 이진 트리 `left | right` (좌→우 순서로 파이프)
- 메모리 소유권
  - `argv[]`, `redirs[]`, `t_ast`는 파서가 생성·해제. exec는 참조만 하며 해제하지 않음.

### 리다이렉션 구조(t_redir)
- 필드 의미
  - `kind`: `R_IN/R_OUT/R_APP/R_HERE`
  - `target`: 확장+따옴표 제거 완료된 최종 문자열(heredoc 본문 제외)
  - `quoted`: heredoc 정책 판단용(exec는 사용 X)
  - `ambig`: 모호하면 1로 세팅(exec가 메시지 출력 후 실패 처리)
  - `here_fd`: heredoc read fd(≥0). exec는 `dup2(here_fd, STDIN)` 후 닫음.
- 모호(ambiguous) 판정 예시
  - `unset A; echo hi > $A` → target = "" → `ambig=1` → 실행 전: `minishell: : ambiguous redirect`
  - `A="foo bar"; echo hi > $A` → target = "foo bar" (공백 포함) → `ambig=1`
  - `A=foo; echo hi > $A` → target = "foo" → 정상

## 확장(파서/확장 팀 담당)
- 변수: `$VAR`, `$?` 확장(미정의=빈 문자열)
- 따옴표: 작은따옴표 내 확장 금지, 큰따옴표 내 허용
- 워드 스플리팅 없음: 확장으로 생긴 공백은 argv 분리하지 않음
- 예시
  - `VAR="a b"; echo $VAR` → argv = ["echo", "a b"]
  - `echo "$HOME"` → argv = ["echo", "/home/user"]
  - `echo '$HOME'` → argv = ["echo", "$HOME"]
  - `echo $?` → argv = ["echo", "<직전 상태코드>"]

## Heredoc(프로듀서, 팀 담당)
- 파서/전처리에서 수행: delimiter 인용 여부에 따라 내용 확장 여부 결정, Ctrl-C(130) 처리, 내용 스트림을 준비해 read end fd를 `t_redir.here_fd`로 전달.
- exec 측: `here_fd`만 STDIN으로 `dup2` 후 닫음(내용 생성/확장은 하지 않음).
- 예시
  - `cat <<EOF` (unquoted) → heredoc 본문에서 `$VAR` 확장
  - `cat <<'EOF'` (quoted) → 확장 금지(리터럴)

## 에러/상태코드 정책 (bash 톤)
- not found(127): 슬래시 없는 이름 + PATH 탐색 실패
  - 예: `minishell: cmdX: command not found`
- 126류: 경로 문제/권한/형식(ENOEXEC/EISDIR/ELOOP/EACCES 등)
  - 예: `minishell: /tmp/noexec.sh: Permission denied`
  - 예: `minishell: /: Is a directory`
  - 예: `minishell: ./badfmt: Exec format error`
- ambiguous redirect: 파서가 `ambig=1` 세팅 시
  - 예: `minishell: foo bar: ambiguous redirect`
- 구문 오류(파서 책임): 메시지 출력 후 258 반환, exec 호출 금지
  - 예: `| ls`, `ls | | wc`, `echo >` 등 → 258

## 시그널/EOF 경계 (Ctrl-C / Ctrl-\ / Ctrl-D)
- 자식(팀 담당): SIGINT(CTRL-C)/SIGQUIT(CTRL-\) 처리는 팀 구현에 따름(종료코드 `128+신호` 기대; INT=130, QUIT=131). 현재 레포의 `ex_sig_child_default()`는 스모크 테스트 참조용 헬퍼이며, exec 경로에서 강제로 호출하지 않습니다.
- 부모(인터랙티브, 팀 담당): readline 루프에서 설정
  - 초기: `ex_sig_parent_interactive()` 1회 호출(SIGQUIT 무시)
  - SIGINT(CTRL-C) 핸들러 예:
    ```c
    void on_sigint(int sig) {
        (void)sig;
        rl_on_new_line();
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_redisplay();
        g_last_status = 130;
    }
    signal(SIGINT, on_sigint);
    ```
  - SIGQUIT(CTRL-\): 인터랙티브에서는 기본적으로 무시(출력 없음). 파이프라인/자식에서 종료코드 131이 반영되도록 함.
  - EOF(CTRL-D): 시그널이 아니라 터미널 EOF. `readline()`이 `NULL`을 반환하면 셸을 종료.
    - 권장 동작: 빈 프롬프트에서 CTRL-D 입력 시 `exit`를 출력하고 마지막 상태코드로 종료.
    - 예:
      ```c
      char *line = readline(prompt);
      if (!line) { // CTRL-D
          printf("exit\n");
          exit(g_last_status); // 팀 정책에 따라 0 또는 마지막 코드
      }
      ```

## 부모 내장/종료 연동
- 부모 내장: `cd/export/unset/exit`는 부모에서 실행 → env/종료에 영향
- exit 처리: `builtin_exec_parent("exit", ...)`가 `rc>=256` 로 "진짜 종료" 신호 → 외부 루프에서 `exit(rc-256)`
  - 예:
    ```c
    int rc = execute_ast(ast, &env);
    if (rc >= 256) exit(rc - 256);
    g_last_status = rc;
    ```

## 흔한 함정과 체크리스트
- argv/argc 일치: `argv`는 NULL-terminated, `argc`는 실제 개수
- 리다이렉션 배열: `redirs` 포인터/`n_redirs` 개수 일관 유지
- heredoc fd 유효성: `here_fd >= 0`일 때만 exec에서 소비, 소비 후 반드시 -1로 무효화하거나 호출 측에서 해제
- 파이프라인 내 부모 내장 영향 금지: `export A=A | cat` 수행 후 부모 env에 A가 생기면 안 됨
- PATH 비설정/빈 문자열: 슬래시 없는 명령은 127. 슬래시 포함 경로는 PATH 무시
- 에러 메시지 중복 방지: fd 유틸은 perror 출력 안 함(상위에서 통일 출력)

## 통합 후 스모크 예시
- 구문 오류 → 258, exec 미호출
  - `| ls`, `ls | | wc`, `echo >` …
- ambiguous redirect
  - `unset A; echo hi > $A` → `minishell: : ambiguous redirect`
  - `A="x y"; echo > $A` → `minishell: x y: ambiguous redirect`
- heredoc (팀 구현 후)
  - `cat <<EOF` + `$HOME` 포함 → 확장되어 들어가야 함(unquoted delimiter)
  - `cat <<'EOF'` + `$HOME` 포함 → 확장 금지(quoted delimiter)
  - Ctrl-C 중단 → 130
- 시그널
  - `sh -c 'kill -INT $$'` → 130
  - `printf A | sh -c 'kill -INT $$'` → 130(마지막 프로세스 코드)
- 에러 메시지
  - not found: `minishell: cmdX: command not found`
  - 권한: `minishell: /tmp/noexec.sh: Permission denied`
  - 디렉토리 실행: `minishell: /: Is a directory`
  - 포맷: `minishell: ./badfmt: Exec format error`

## 빌드/테스트 안내(참고)
- 테스트 빌드: `make -C tests -j4`
- 실행: `./tests/resolve_smoke`, `./tests/executor_core_smoke`, `./tests/executor_more_smoke`, `./tests/signal_smoke`

---
문의/수정이 필요한 포인트가 있으면 본 문서를 갱신하면서 진행해 주세요. 이 계약을 만족하면, 각 파트가 별도로 개발되어도 최종 병합 시 추가 수정 없이 동작합니다.
