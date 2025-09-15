/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:43:38 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 14:51:02 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

// -n, -nn, -nnn 처럼 n이 오는 경우만 true.
// -n -n
static int	is_echo_nopt(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

static int	builtin_echo(char **argv)
{
	int	i;
	int	no_nl;
	int	first;

	i = 1;
	no_nl = 0;
	while (argv[i] && is_echo_nopt(argv[i]))
	{
		no_nl = 1;
		i++;
	}
	first = 1;
	while (argv[i])
	{
		if (!first)
			write(1, " ", 1);
		write(1, argv[i], (int)ft_strlen(argv[i]));
		first = 0;
		i++;
	}
	if (!no_nl)
		write(1, "\n", 1);
	return (0);
}

static int	builtin_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)))
	{
		printf("%s\n", buf);
		return (0);
	}
	perror("pwd");
	return (1);
}

static int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
		return (0);
	}
}
int	builtin_exec_child(t_builtin k, char **argv, t_env *env)
{
	if (k == BUILTIN_ECHO)
		return (builtin_echo(argv));
	if (k == BUILTIN_PWD)
		return (builtin_pwd());
	if (k == BUILTIN_ENV)
		return (builtin_env(env));
	return (1);
}
