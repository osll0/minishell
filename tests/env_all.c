#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "env.h"
#include "libft.h"

/* --- helpers --- */
static int contains_line(const char *hay, const char *needle)
{
	size_t nlen;

	if (hay == NULL || needle == NULL)
		return (0);
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return (1);
	if (ft_strnstr(hay, needle, ft_strlen(hay)) != NULL)
		return (1);
	return (0);
}

static int read_all(int fd, char **out, size_t *outlen)
{
	size_t cap = 4096;
	size_t len = 0;
	char *buf = (char *)malloc(cap);
	ssize_t r;

	if (!buf)
		return (-1);
	while (1)
	{
		if (len + 2048 > cap)
		{
			size_t ncap = cap * 2;
			char *nbuf = (char *)realloc(buf, ncap);
			if (!nbuf) { free(buf); return (-1); }
			buf = nbuf;
			cap = ncap;
		}
		r = read(fd, buf + len, 2048);
		if (r < 0) { free(buf); return (-1); }
		if (r == 0) break;
		len += (size_t)r;
	}
	buf[len] = '\0';
	*out = buf;
	if (outlen) *outlen = len;
	return (0);
}

/* --- unit A: env API (set/overwrite/unset, EMPTY) --- */
static int test_env_api_from_environ(char **environ)
{
	t_env *env;
	char **arr;
	int rc;

	env = env_from_environ(environ);
	if (!env) { printf("[FAIL] env_from_environ\n"); return (1); }

	/* set */
	rc = env_set(&env, "FOO", "BAR");
	if (rc == -1 || !env_get(env, "FOO")) { printf("[FAIL] env_set FOO\n"); env_free(&env); return (1); }

	/* overwrite */
	rc = env_set(&env, "FOO", "BAZ");
	if (rc == -1 || !env_get(env, "FOO") || ft_strcmp(env_get(env, "FOO"), "BAZ") != 0)
	{ printf("[FAIL] overwrite FOO\n"); env_free(&env); return (1); }

	/* unset */
	rc = env_unset(&env, "FOO");
	if (rc != 0 || env_get(env, "FOO") != NULL) { printf("[FAIL] unset FOO\n"); env_free(&env); return (1); }

	/* EMPTY (NULL value → "KEY=") */
	rc = env_set(&env, "EMPTY", NULL);
	if (rc == -1) { printf("[FAIL] set EMPTY=NULL\n"); env_free(&env); return (1); }
	arr = env_to_array(env);
	if (!arr) { printf("[FAIL] env_to_array\n"); env_free(&env); return (1); }

	/* 확인: 배열에 "EMPTY=" 포함 */
	int ok = 0;
	for (size_t i = 0; arr[i]; i++)
		if (ft_strncmp(arr[i], "EMPTY=", 6) == 0)
			ok = 1;
	if (!ok) { printf("[FAIL] array missing EMPTY=\n"); free_env_array(arr); env_free(&env); return (1); }

	free_env_array(arr);
	env_free(&env);
	printf("[ OK ] env API (set/overwrite/unset, EMPTY)\n");
	return (0);
}

/* --- unit B: execve 환경 전달 --- */
static int test_execve_env_propagation(char **environ)
{
	int fds[2];
	pid_t pid;
	char *out = NULL;

	if (pipe(fds) == -1) { perror("pipe"); return (1); }
	pid = fork();
	if (pid == -1) { perror("fork"); close(fds[0]); close(fds[1]); return (1); }

	if (pid == 0)
	{
		/* child: build env, set key, execve("/usr/bin/env") with our envp */
		t_env *env = env_from_environ(environ);
		if (!env) _exit(127);
		if (env_set(&env, "DEMO_KEY", "DEMO_VAL") == -1) _exit(127);

		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);

		char **arr = env_to_array(env);
		if (!arr) _exit(127);
		char *argv[] = {"/usr/bin/env", NULL};
		execve("/usr/bin/env", argv, arr);
		/* 실패 시에만 여기 도달 */
		perror("execve");
		free_env_array(arr);
		env_free(&env);
		_exit(127);
	}
	/* parent */
	close(fds[1]);
	if (read_all(fds[0], &out, NULL) == -1) { perror("read_all"); close(fds[0]); return (1); }
	close(fds[0]);

	int status = 0;
	waitpid(pid, &status, 0);
	if (!out) { printf("[FAIL] no child output\n"); return (1); }
	if (!contains_line(out, "DEMO_KEY=DEMO_VAL"))
	{
		printf("[FAIL] execve env missing DEMO_KEY\n");
		free(out);
		return (1);
	}
	free(out);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
	{
		printf("[WARN] child exit status != 0 (but env present)\n");
		/* 그래도 환경 전달 확인 되었으니 통과로 간주 */
	}
	printf("[ OK ] execve propagation (DEMO_KEY=DEMO_VAL)\n");
	return (0);
}

int main(int ac, char **av, char **environ)
{
	int fail = 0;
	(void)ac; (void)av;

	fail |= test_env_api_from_environ(environ);
	fail |= test_execve_env_propagation(environ);

	if (fail == 0)
	{
		printf("\n=== ALL TESTS PASSED ===\n");
		return (0);
	}
	printf("\n=== SOME TESTS FAILED ===\n");
	return (1);
}

