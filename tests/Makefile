CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I../include -I../libft
LIBFT_DIR := ../libft
LIBFT   := $(LIBFT_DIR)/libft.a

# --- builtin smoke ---
BUILTIN_SRCS := \
  ../src/builtin/builtin_lookup.c \
  ../src/builtin/builtin_child.c \
  ../src/builtin/builtin_parent.c \
  ../src/builtin/builtin_echo.c \
  ../src/builtin/builtin_pwd.c \
  ../src/builtin/builtin_env.c \
  ../src/builtin/builtin_cd.c \
  ../src/builtin/builtin_export.c \
  ../src/builtin/builtin_unset.c \
  ../src/builtin/builtin_exit.c \
  ../src/builtin/builtin_utils.c \
  ../src/builtin/builtin_options.c

# --- env 모듈 ---
ENV_SRCS := \
  ../src/env/env_from_environ.c \
  ../src/env/env_list.c \
  ../src/env/env_utils.c \
  ../src/env/env_to_array.c

# --- fd 래퍼들 ---
FD_SRCS := \
  ../src/fd/fd_open.c \
  ../src/fd/fd_dup_close.c \
  ../src/fd/fd_pipe.c \
  ../src/fd/fd_pipes_array.c

# --- exec core (resolve + helpers) ---
EXEC_SRCS := \
  ../src/exec/split_path.c \
  ../src/exec/exec_errors.c

# --- executor 통합용 exec 소스 ---
EXECUTOR_SRCS := \
  ../src/exec/executor.c \
  ../src/exec/executor_single.c \
  ../src/exec/executor_pipe.c \
  ../src/exec/executor_stage.c \
  ../src/exec/exec_parent_redir.c \
  ../src/exec/child_exec.c \
  ../src/exec/redir.c \
  ../src/exec/exec_helpers.c \
  ../src/exec/resolve_path.c \
  ../src/exec/resolve_entry.c \
  $(EXEC_SRCS) \
  $(FD_SRCS)

# --- 테스트 소스 (정리: builtin / env / fd / exec_compare) ---
BUILTIN_TEST_SRCS  := builtin_smoke.c
ENV_TEST_SRCS      := env_smoke.c
FD_TEST_SRCS       := fd_smoke.c
COMPARE_TEST_SRCS  := exec_compare.c

# --- 타깃 ---
BUILTIN_TARGET   := builtin_smoke
ENV_TARGET       := env_smoke
FD_TARGET        := fd_smoke
COMPARE_TARGET   := exec_compare

ALL_TARGETS := \
  $(BUILTIN_TARGET) \
  $(ENV_TARGET) \
  $(FD_TARGET) \
  $(COMPARE_TARGET)

all: $(ALL_TARGETS)

# --- 링크 규칙 ---
$(BUILTIN_TARGET): $(BUILTIN_SRCS:.c=.o) $(ENV_SRCS:.c=.o) $(BUILTIN_TEST_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(ENV_TARGET): $(ENV_SRCS:.c=.o) $(ENV_TEST_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(FD_TARGET): $(FD_SRCS:.c=.o) $(FD_TEST_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

# ★ 추가: signal_smoke (SIGINT/SIGQUIT 반환코드/파이프라인 확인)
$(SIGNAL_TARGET): $(EXECUTOR_SRCS:.c=.o) $(ENV_SRCS:.c=.o) $(BUILTIN_SRCS:.c=.o) $(SIGNAL_TEST_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

# ★ 추가: exec_compare (bash와 출력/코드 비교)
$(COMPARE_TARGET): $(EXECUTOR_SRCS:.c=.o) $(ENV_SRCS:.c=.o) $(BUILTIN_SRCS:.c=.o) $(COMPARE_TEST_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

# --- 컴파일 ---
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- libft ---
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# --- 정리 ---
clean:
	rm -f \
	  $(BUILTIN_SRCS:.c=.o) \
	  $(ENV_SRCS:.c=.o) \
	  $(FD_SRCS:.c=.o) \
	  $(EXEC_SRCS:.c=.o) \
	  $(EXECUTOR_SRCS:.c=.o) \
	  $(BUILTIN_TEST_SRCS:.c=.o) \
	  $(ENV_TEST_SRCS:.c=.o) \
	  $(FD_TEST_SRCS:.c=.o) \
	  $(COMPARE_TEST_SRCS:.c=.o)

fclean: clean
	rm -f $(ALL_TARGETS)

re: fclean all

.PHONY: all clean fclean re

# Optional: remove test artifacts explicitly
clean-artifacts:
	rm -f /tmp/ms.out /tmp/ms.err /tmp/bash.out /tmp/bash.err \
	      /tmp/noexec.sh /tmp/nondir_path_elem /tmp/exp_cmp.txt \
	      /tmp/ms_r.txt /tmp/bash_r.txt /tmp/in_cmp.txt \
	      /tmp/ms_r_out.txt /tmp/bash_r_out.txt \
	      /tmp/fd_t.txt
	rm -f ./rel_noexec.sh ./rel_ok.sh ./rel_ok2.sh ./badfmt ./loopexe
	rm -rf ./a ./b ./echo ./nodx

.PHONY: clean-artifacts
