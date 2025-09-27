// tests/builtin_smoke.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "env.h"
#include "builtin.h"

/* 간단 룩업: exec 쪽과 동일 enum 매핑 */
static t_builtin lookup(const char *s)
{
	if (!s) return BUILTIN_NONE;
	if (ft_strcmp(s, "echo") == 0) return BUILTIN_ECHO;
	if (ft_strcmp(s, "pwd") == 0) return BUILTIN_PWD;
	if (ft_strcmp(s, "env") == 0) return BUILTIN_ENV;
	if (ft_strcmp(s, "cd") == 0) return BUILTIN_CD;
	if (ft_strcmp(s, "export") == 0) return BUILTIN_EXPORT;
	if (ft_strcmp(s, "unset") == 0) return BUILTIN_UNSET;
	if (ft_strcmp(s, "exit") == 0) return BUILTIN_EXIT;
	return BUILTIN_NONE;
}

static int is_parent_builtin(t_builtin k)
{
	return (k == BUILTIN_CD || k == BUILTIN_EXPORT || k == BUILTIN_UNSET || k == BUILTIN_EXIT);
}

static void free_argv(char **argv)
{
	size_t i = 0;
	if (!argv) return;
	while (argv[i]) { free(argv[i]); i++; }
	free(argv);
}

/* 공백 기준 토크나이즈(따옴표/이스케이프는 미지원: smoke 용) */
static char **split_argv(const char *line)
{
	char **parts = NULL;
	char *dup = NULL;
	size_t i;

	if (!line) return NULL;
	dup = ft_strdup(line);
	if (!dup) return NULL;
	i = ft_strlen(dup);
	if (i && dup[i - 1] == '\n') dup[i - 1] = '\0';
	parts = ft_split(dup, ' ');
	free(dup);
	return parts;
}

int main(int argc, char **argv, char **environ)
{
	t_env *env_head;
	char buf[4096];

	(void)argc; (void)argv;
	env_head = env_from_environ(environ);
	if (!env_head) { fprintf(stderr, "env init failed\n"); return 1; }

	printf("builtin_smoke REPL (echo/pwd/env | cd/export/unset/exit)\n");
	printf("type commands; Ctrl-D to quit. example: export FOO=BAR\n\n");
	while (fgets(buf, sizeof(buf), stdin))
	{
		char **av = split_argv(buf);
		t_builtin k;
		int rc;

		if (!av || !av[0]) { free_argv(av); continue; }
		k = lookup(av[0]);
		if (k == BUILTIN_NONE)
		{
			printf("[info] not a builtin: %s\n", av[0]);
			free_argv(av);
			continue;
		}
		if (is_parent_builtin(k))
		{
			rc = builtin_exec_parent(k, av, &env_head);
			if (rc >= 256)
			{
				int code = rc - 256;
				free_argv(av);
				env_free(&env_head);
				exit(code);
			}
			printf("[parent rc=%d]\n", rc);
		}
		else
		{
			rc = builtin_exec_child(k, av, env_head);
			printf("[child rc=%d]\n", rc);
		}
		free_argv(av);
	}
	env_free(&env_head);
	return 0;
}

