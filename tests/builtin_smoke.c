/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_smoke.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:38:39 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 18:45:16 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>

static int	run_echo(char **av)
{
	t_env	*env;

	env = NULL;
	return builtin_exec_child(BUILTIN_ECHO, av, env);
}

static int	run_pwd(void) {
	t_env *env = NULL;
	char *av[] = { "pwd", "i--", NULL };
	(void)env;
	return builtin_exec_child(BUILTIN_PWD, av, env);
}

static int run_env(void) {
	/* env는 NULL이므로 출력 없음(크래시 안 나는지만 확인) */
	t_env *env = NULL;
	char *av[] = { "env", "-a", NULL };
	return builtin_exec_child(BUILTIN_ENV, av, env);
}

int main(void) {
	int rc;
	/* echo */
	{ char *av[] = {"echo","-nna","world",NULL}; rc = run_echo(av);
		printf("[echo] rc=%d (expect 0)\n", rc); }

	/* echo -n -n */
	{ char *av[] = {"echo","-nnn","-n","HI",NULL}; rc = run_echo(av);
		printf("[echo -n -n] rc=%d (expect 0)\n", rc); }

	/* pwd */
	rc = run_pwd();
	printf("[pwd] rc=%d (expect 0)\n", rc);

	/* env (NULL 리스트) */
	rc = run_env();
	printf("[env(NULL)] rc=%d (expect 0)\n", rc);

	/* parent stubs */
	/*
	{
		t_env *env = NULL;
		char *cdv[] = {"cd","/",NULL};
		rc = builtin_exec_parent(BUILTIN_CD, cdv, env);
		printf("[cd stub] rc=%d (expect 1)\n", rc);
	}
	*/
	return 0;
}
