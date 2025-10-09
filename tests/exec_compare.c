/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:40:00 by seokson           #+#    #+#             */
/*   Updated: 2025/10/06 16:40:00 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "env.h"
#include "ast.h"
#include "exec.h"
#include "libft.h"

/* ---- small io helpers ---- */
static int same_file(const char *a, const char *b)
{
    FILE *fa = fopen(a, "rb");
    FILE *fb = fopen(b, "rb");
    int ra = -1, rb = -1;
    int eq = 1;
    if (!fa || !fb) { if (fa) fclose(fa); if (fb) fclose(fb); return 0; }
    for (;;) {
        ra = fgetc(fa); rb = fgetc(fb);
        if (ra != rb) { eq = 0; break; }
        if (ra == EOF || rb == EOF) break;
    }
    fclose(fa); fclose(fb);
    return eq;
}

static int capture_fds_begin(int *save_out, int *save_err, const char *outp, const char *errp)
{
    int fd_out = open(outp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd_err = open(errp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0 || fd_err < 0) return -1;
    *save_out = dup(STDOUT_FILENO);
    *save_err = dup(STDERR_FILENO);
    if (*save_out < 0 || *save_err < 0) return -1;
    dup2(fd_out, STDOUT_FILENO);
    dup2(fd_err, STDERR_FILENO);
    close(fd_out); close(fd_err);
    return 0;
}

static void capture_fds_end(int save_out, int save_err)
{
    if (save_out >= 0) { dup2(save_out, STDOUT_FILENO); close(save_out); }
    if (save_err >= 0) { dup2(save_err, STDERR_FILENO); close(save_err); }
}

static int g_tap_idx = 0;
static int g_fail = 0;

static void dump_file(const char *title, const char *path)
{
    FILE *f = fopen(path, "rb");
    int c;
    printf("  # %s (%s):\n", title, path);
    if (!f) { printf("  #   (missing)\n"); return; }
    printf("  #   ");
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
            printf("\n  #   ");
        else
            fputc(c, stdout);
    }
    printf("\n");
    fclose(f);
}

/* KO 조건: rc가 다를 때만. 출력 차이는 참고용으로 덤프 */
static void tap_cmp(const char *label, int rc_o, int rc_b, int eq_out, int eq_err)
{
    int ok_rc = (rc_o == rc_b);
    g_tap_idx++;
    if (ok_rc)
        printf("ok %d - %s\n", g_tap_idx, label);
    else {
        printf("not ok %d - %s\n", g_tap_idx, label);
        printf("  # diag: rc ours=%d bash=%d\n", rc_o, rc_b);
        g_fail++;
    }
    if (!eq_out)
    {
        printf("  # diag: stdout differs\n");
        dump_file("stdout (ours)", "/tmp/ms.out");
        dump_file("stdout (bash)", "/tmp/bash.out");
    }
    if (!eq_err)
    {
        printf("  # diag: stderr differs\n");
        dump_file("stderr (ours)", "/tmp/ms.err");
        dump_file("stderr (bash)", "/tmp/bash.err");
    }
}

/* ---- builders ---- */
static int argc_of(char **argv){int n=0;while(argv&&argv[n])n++;return n;}
static char **argv3(const char *a, const char *b, const char *c){char **v=(char**)ft_calloc(4,sizeof(char*));int i=0; if(!v)return NULL; if(a)v[i++]=ft_strdup(a); if(b)v[i++]=ft_strdup(b); if(c)v[i++]=ft_strdup(c); v[i]=NULL; return v;}
static char **argv2(const char *a, const char *b){return argv3(a,b,NULL);} 
static void freev(char **v){int i=0; if(!v)return; while(v[i]) free(v[i++]); free(v);} 

static t_ast *node_cmdv(char **v){ t_ast *n=(t_ast*)ft_calloc(1,sizeof(t_ast)); if(!n)return NULL; n->type=N_CMD; n->cmd.argv=v; n->cmd.argc=argc_of(v); return n;}
static t_ast *node_pipe(t_ast *l, t_ast *r){ t_ast *n=(t_ast*)ft_calloc(1,sizeof(t_ast)); if(!n)return NULL; n->type=N_PIPE; n->left=l; n->right=r; return n;}
static void free_ast_all(t_ast *n){ if(!n)return; if(n->type==N_PIPE){ free_ast_all(n->left); free_ast_all(n->right); free(n); return;} if(n->type==N_CMD) freev(n->cmd.argv); free(n);} 

/* forward decls */
static void set_default_path(t_env **penv);

/* ---- run helpers ---- */
static int run_single_capture_keep(const char *label, t_env **penv, char **v,
                                   const char *bash, const char *op, const char *ep)
{
    int save_out=-1, save_err=-1; int rc_o, rc_b; char cmd[1024];
    t_cmd c; memset(&c,0,sizeof(c)); c.argv=v; c.argc=argc_of(v);
    if (capture_fds_begin(&save_out, &save_err, op, ep) < 0) return 1;
    rc_o = execute_single_cmd(&c, penv);
    capture_fds_end(save_out, save_err);
    snprintf(cmd,sizeof(cmd),"bash -c '%s' >/tmp/bash.out 2>/tmp/bash.err", bash);
    rc_b = system(cmd); if (WIFEXITED(rc_b)) rc_b=WEXITSTATUS(rc_b); else if (WIFSIGNALED(rc_b)) rc_b=128+WTERMSIG(rc_b);
    tap_cmp(label, rc_o, rc_b, same_file(op,"/tmp/bash.out"), same_file(ep,"/tmp/bash.err"));
    return 0;
}

static int run_single_capture(const char *label, t_env **penv, char **v,
                              const char *bash, const char *op, const char *ep)
{
    set_default_path(penv);
    return run_single_capture_keep(label, penv, v, bash, op, ep);
}

static int run_pipe_capture(const char *label, t_env **penv, t_ast *p,
                            const char *bash, const char *op, const char *ep)
{
    int save_out=-1, save_err=-1; int rc_o, rc_b; char cmd[1024];
    if (capture_fds_begin(&save_out, &save_err, op, ep) < 0) return 1;
    rc_o = execute_pipe(p, penv);
    capture_fds_end(save_out, save_err);
    snprintf(cmd,sizeof(cmd),"bash -c '%s' >/tmp/bash.out 2>/tmp/bash.err", bash);
    rc_b = system(cmd); if (WIFEXITED(rc_b)) rc_b=WEXITSTATUS(rc_b); else if (WIFSIGNALED(rc_b)) rc_b=128+WTERMSIG(rc_b);
    tap_cmp(label, rc_o, rc_b, same_file(op,"/tmp/bash.out"), same_file(ep,"/tmp/bash.err"));
    return 0;
}

/* ---- redirection compare (our exec redir vs bash redir) ---- */
static int run_our_redir(t_env **penv, char **v, t_redir *rr, int n)
{
    t_cmd c; memset(&c,0,sizeof(c)); c.argv=v; c.argc=argc_of(v); c.redirs=rr; c.n_redirs=n;
    return execute_single_cmd(&c, penv);
}

static int run_bash_line(const char *line)
{
    int rc; char cmd[1024];
    snprintf(cmd,sizeof(cmd),"bash -c '%s'", line);
    rc = system(cmd);
    if (WIFEXITED(rc)) return WEXITSTATUS(rc);
    if (WIFSIGNALED(rc)) return 128+WTERMSIG(rc);
    return 1;
}

static void tap_file_eq(const char *label, const char *path_ms, const char *path_bash, int rc_o, int rc_b)
{
    int eq = same_file(path_ms, path_bash);
    g_tap_idx++;
    if (rc_o==rc_b && eq) printf("ok %d - %s\n", g_tap_idx, label);
    else {
        printf("not ok %d - %s\n", g_tap_idx, label);
        if (rc_o!=rc_b) printf("  # diag: rc ours=%d bash=%d\n", rc_o, rc_b);
        if (!eq) printf("  # diag: file differs (%s vs %s)\n", path_ms, path_bash);
        g_fail++;
    }
}

static void run_our_with_redirs_capture(const char *label, t_env **penv,
                                        char **v, t_redir *rr, int n,
                                        const char *bash_line)
{
    int save_out=-1, save_err=-1; int rc_o, rc_b; char cmd[1024];
    t_cmd c; memset(&c,0,sizeof(c)); c.argv=v; c.argc=argc_of(v); c.redirs=rr; c.n_redirs=n;
    if (capture_fds_begin(&save_out, &save_err, "/tmp/ms.out", "/tmp/ms.err") < 0) return;
    rc_o = execute_single_cmd(&c, penv);
    capture_fds_end(save_out, save_err);
    snprintf(cmd,sizeof(cmd),"bash -c '%s' >/tmp/bash.out 2>/tmp/bash.err", bash_line);
    rc_b = system(cmd); if (WIFEXITED(rc_b)) rc_b=WEXITSTATUS(rc_b); else if (WIFSIGNALED(rc_b)) rc_b=128+WTERMSIG(rc_b);
    tap_cmp(label, rc_o, rc_b, same_file("/tmp/ms.out","/tmp/bash.out"), same_file("/tmp/ms.err","/tmp/bash.err"));
}

static void set_default_path(t_env **penv)
{
    env_set(penv, "PATH", "/bin:/usr/bin");
}

int main(int argc, char **argv, char **envp)
{
    (void)argc; (void)argv;
    t_env *env = env_from_environ((char *const *)envp);
    if (!env) { fprintf(stderr, "env init failed\n"); return 1; }
    system("rm -f /tmp/ms.out /tmp/ms.err /tmp/bash.out /tmp/bash.err");

    /* TAP plan (마지막에 출력) */

    /* --- resolve / errors --- */
    set_default_path(&env);
    run_single_capture("PATH echo", &env, argv2("echo","OK"), "echo OK", "/tmp/ms.out", "/tmp/ms.err");
    run_single_capture("/bin/echo", &env, argv2("/bin/echo","OK"), "/bin/echo OK", "/tmp/ms.out", "/tmp/ms.err");
    run_single_capture("notfound 127", &env, argv2("__NO_SUCH_CMD__",NULL), "__NO_SUCH_CMD__", "/tmp/ms.out", "/tmp/ms.err");

    system("echo 'echo denied' > /tmp/noexec.sh; chmod 644 /tmp/noexec.sh");
    run_single_capture("noexec 126", &env, argv2("/tmp/noexec.sh",NULL), "/tmp/noexec.sh", "/tmp/ms.out", "/tmp/ms.err");
    run_single_capture("dir exec 126", &env, argv2("/",NULL), "/", "/tmp/ms.out", "/tmp/ms.err");

    /* PATH empty → 127 */
    env_set(&env, "PATH", "");
    run_single_capture_keep("PATH empty", &env, argv2("echo","OK"), "PATH= echo OK", "/tmp/ms.out", "/tmp/ms.err");
    env_set(&env, "PATH", "/bin:/usr/bin");

    /* ENOTDIR path element */
    system("echo X >/tmp/nondir_path_elem; chmod 644 /tmp/nondir_path_elem");
    env_set(&env, "PATH", "/tmp/nondir_path_elem:/bin");
    run_single_capture_keep("PATH ENOTDIR then /bin", &env, argv2("echo","OK"), "PATH=/tmp/nondir_path_elem:/bin echo OK", "/tmp/ms.out", "/tmp/ms.err");

    /* relative not exist -> 127 */
    run_single_capture("./not_exist 127", &env, argv2("./not_exist_zzz",NULL), "./not_exist_zzz", "/tmp/ms.out", "/tmp/ms.err");
    /* relative noexec -> 126 */
    system("echo '#!/bin/sh\necho HI' > ./rel_noexec.sh; chmod 644 ./rel_noexec.sh");
    run_single_capture("./rel_noexec 126", &env, argv2("./rel_noexec.sh",NULL), "./rel_noexec.sh", "/tmp/ms.out", "/tmp/ms.err");
    /* relative exec success with PATH ignored */
    system("echo '#!/bin/sh\necho REL_OK' > ./rel_ok.sh; chmod 755 ./rel_ok.sh");
    env_set(&env, "PATH", "");
    run_single_capture_keep("./rel_ok path ignored", &env, argv2("./rel_ok.sh",NULL), "./rel_ok.sh", "/tmp/ms.out", "/tmp/ms.err");
    env_unset(&env, "PATH");
    run_single_capture_keep("./rel_ok PATH unset", &env, argv2("./rel_ok.sh",NULL), "./rel_ok.sh", "/tmp/ms.out", "/tmp/ms.err");
    env_set(&env, "PATH", "/bin:/usr/bin");
    /* bad format -> 126 */
    system("printf '\\x7FNOTELF' > ./badfmt; chmod 755 ./badfmt");
    run_single_capture("badfmt 126", &env, argv2("./badfmt",NULL), "./badfmt", "/tmp/ms.out", "/tmp/ms.err");
    /* symlink loop -> 126 */
    system("rm -f ./loopexe; ln -s loopexe ./loopexe");
    run_single_capture("symlink loop 126", &env, argv2("./loopexe",NULL), "./loopexe", "/tmp/ms.out", "/tmp/ms.err");

    /* PATH with leading empty element ':' includes current dir */
    system("echo '#!/bin/sh\necho REL_OK2' > ./rel_ok2.sh; chmod 755 ./rel_ok2.sh");
    env_set(&env, "PATH", ":/bin:/usr/bin");
    run_single_capture_keep("PATH ':/bin' + rel_ok2", &env, argv2("rel_ok2.sh",NULL), "PATH=:/bin:/usr/bin rel_ok2.sh", "/tmp/ms.out", "/tmp/ms.err");

    /* PATH trailing ':' includes current dir */
    env_set(&env, "PATH", "/bin:/usr/bin:");
    run_single_capture_keep("PATH '/bin:' + rel_ok2", &env, argv2("rel_ok2.sh",NULL), "PATH=/bin:/usr/bin: rel_ok2.sh", "/tmp/ms.out", "/tmp/ms.err");

    /* PATH duplicate element priority */
    system("mkdir -p ./a ./b; echo '#!/bin/sh\necho A' > ./a/cmdX; chmod 755 ./a/cmdX; echo '#!/bin/sh\necho B' > ./b/cmdX; chmod 755 ./b/cmdX");
    env_set(&env, "PATH", "./a:./b:/bin:/usr/bin");
    run_single_capture_keep("PATH priority a over b", &env, argv2("cmdX",NULL), "PATH=./a:./b:/bin:/usr/bin cmdX", "/tmp/ms.out", "/tmp/ms.err");

    /* PATH element with no search-x only */
    system("mkdir -p ./nodx; chmod 600 ./nodx; echo '#!/bin/sh\necho NX' > ./nodx/hello; chmod 755 ./nodx/hello");
    env_set(&env, "PATH", "./nodx");
    run_single_capture_keep("PATH dir no-x only -> 126", &env, argv2("hello",NULL), "PATH=./nodx hello", "/tmp/ms.out", "/tmp/ms.err");
    system("chmod 700 ./nodx");

    /* --- redirections via argv echo; compare stderr on error --- */
    set_default_path(&env);
    run_single_capture("redir ok", &env, argv3("bash","-c","echo A"), "echo A", "/tmp/ms.out", "/tmp/ms.err");
    /* invalid target: '>' to '/' */
    run_single_capture("redir err > /", &env, argv3("bash","-c","echo A > /"), "echo A > /", "/tmp/ms.out", "/tmp/ms.err");

    /* ambiguous redirect: unset A; echo > $A */
    env_unset(&env, "A");
    run_single_capture("ambiguous > $A", &env, argv3("bash","-c","unset A; echo hi > $A"), "unset A; echo hi > $A", "/tmp/ms.out", "/tmp/ms.err");

    /* --- our redir vs bash redir: file compare --- */
    set_default_path(&env);
    {
        int rc_o, rc_b; t_redir r; memset(&r,0,sizeof(r));
        /* truncate */
        unlink("/tmp/ms_r.txt"); unlink("/tmp/bash_r.txt");
        r.kind=R_OUT; r.target=(char*)"/tmp/ms_r.txt"; r.ambig=0;
        rc_o = run_our_redir(&env, argv2("echo","A"), &r, 1);
        rc_b = run_bash_line("echo A > /tmp/bash_r.txt");
        tap_file_eq("redir > file compare", "/tmp/ms_r.txt", "/tmp/bash_r.txt", rc_o, rc_b);

        /* append */
        unlink("/tmp/ms_r.txt"); unlink("/tmp/bash_r.txt");
        rc_o = run_bash_line("echo A > /tmp/bash_r.txt");
        rc_b = rc_o;
        r.kind=R_OUT; r.target=(char*)"/tmp/ms_r.txt"; run_our_redir(&env, argv2("echo","A"), &r, 1);
        r.kind=R_APP; r.target=(char*)"/tmp/ms_r.txt"; rc_o = run_our_redir(&env, argv2("echo","B"), &r, 1);
        run_bash_line("echo A > /tmp/bash_r.txt"); run_bash_line("echo B >> /tmp/bash_r.txt");
        tap_file_eq("redir >> append compare", "/tmp/ms_r.txt", "/tmp/bash_r.txt", rc_o, rc_b);

        /* in + out */
        unlink("/tmp/ms_r_out.txt"); unlink("/tmp/bash_r_out.txt");
        run_bash_line("printf IN > /tmp/in_cmp.txt");
        t_redir rr[2]; memset(rr,0,sizeof(rr)); rr[0].kind=R_IN; rr[0].target=(char*)"/tmp/in_cmp.txt"; rr[1].kind=R_OUT; rr[1].target=(char*)"/tmp/ms_r_out.txt";
        rc_o = run_our_redir(&env, argv2("cat",NULL), rr, 2);
        rc_b = run_bash_line("cat < /tmp/in_cmp.txt > /tmp/bash_r_out.txt");
        tap_file_eq("redir <in >out compare", "/tmp/ms_r_out.txt", "/tmp/bash_r_out.txt", rc_o, rc_b);
    }

    /* --- additional redir error comparisons (capture stderr) --- */
    {
        t_redir r; memset(&r,0,sizeof(r));
        /* missing input file */
        r.kind=R_IN; r.target=(char*)"/tmp/__no_such_in.txt"; r.ambig=0;
        run_our_with_redirs_capture("redir < missing in", &env, argv2("cat",NULL), &r, 1, "cat < /tmp/__no_such_in.txt");
        /* no write perm for directory */
        system("rm -rf /tmp/rodir; mkdir /tmp/rodir; chmod 500 /tmp/rodir");
        r.kind=R_OUT; r.target=(char*)"/tmp/rodir/nope.txt"; r.ambig=0;
        run_our_with_redirs_capture("redir > dir no write", &env, argv2("echo","A"), &r, 1, "echo A > /tmp/rodir/nope.txt");
        system("chmod 700 /tmp/rodir; rm -rf /tmp/rodir");
    }

    /* --- pipeline --- */
    set_default_path(&env);
    {
        t_ast *n1 = node_cmdv(argv2("printf","abc"));
        t_ast *n2 = node_cmdv(argv3("tr","a-z","A-Z"));
        t_ast *n3 = node_cmdv(argv2("wc","-c"));
        t_ast *p1 = node_pipe(n1,n2);
        t_ast *p2 = node_pipe(p1,n3);
        run_pipe_capture("pipe 3-stage", &env, p2, "printf abc | tr a-z A-Z | wc -c", "/tmp/ms.out", "/tmp/ms.err");
        free_ast_all(p2);
    }

    /* --- PATH shadow by dir named like cmd (should skip dir) --- */
    system("mkdir -p ./echo; touch ./echo/dummy");
    env_set(&env, "PATH", ".:/bin:/usr/bin");
    run_single_capture_keep("PATH skip dir named echo", &env, argv2("echo","OK"), "PATH=.:/bin:/usr/bin echo OK", "/tmp/ms.out", "/tmp/ms.err");

    /* --- parent builtin with redir: export -- > file --- */
    system("rm -f /tmp/exp_cmp.txt");
    run_single_capture("parent export redir", &env, argv3("bash","-c","export -- > /tmp/exp_cmp.txt"), "export -- > /tmp/exp_cmp.txt", "/tmp/ms.out", "/tmp/ms.err");

    /* TAP plan & summary */
    printf("1..%d\n", g_tap_idx);
    if (g_fail)
        printf("# summary: %d/%d failed\n", g_fail, g_tap_idx);
    else
        printf("# summary: all %d passed\n", g_tap_idx);
    /* cleanup artifacts (KEEP=1 이면 유지) */
    if (!getenv("KEEP")) {
        system("rm -f /tmp/ms.out /tmp/ms.err /tmp/bash.out /tmp/bash.err");
        system("rm -f /tmp/noexec.sh /tmp/nondir_path_elem /tmp/exp_cmp.txt");
        system("rm -f /tmp/ms_r.txt /tmp/bash_r.txt /tmp/in_cmp.txt /tmp/ms_r_out.txt /tmp/bash_r_out.txt");
        system("rm -f ./rel_noexec.sh ./rel_ok.sh ./rel_ok2.sh ./badfmt ./loopexe");
        system("rm -rf ./a ./b ./echo ./nodx");
    } else {
        printf("# KEEP=1: artifacts preserved\n");
    }

    env_free(&env);
    return 0;
}
