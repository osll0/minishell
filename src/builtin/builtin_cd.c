/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:27:08 by seokson           #+#    #+#             */
/*   Updated: 2025/09/21 16:45:58 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "builtin.h"

static int	change_dir_and_update_env(const char *path, t_env **penv)
{
	char	old[4096];
	char	now[4096];

	if (getcwd(old, sizeof(old)) == NULL)
		old[0] = '\0';
	if (chdir(path) != 0)
	{
		bi_print_err("cd", "cannot change directory", path);
		return (1);
	}
	if (getcwd(now, sizeof(now)) != NULL)
	{
		if (old[0] != '\0')
			env_set(penv, "OLDPWD", old);
		env_set(penv, "PWD", now);
	}
	return (0);
}

static int	cd_parse_options(char *const *argv, int *idx)
{
	int	i;

	i = *idx;
	if (argv[i] && bi_is_triple_dash(argv[i]))
	{
		bi_print_err("cd", "invalid option", argv[i]);
		return (2);
	}
	if (argv[i] && bi_is_option_token(argv[i]))
	{
		bi_print_err("cd", "invalid option", argv[i]);
		return (2);
	}
	if (bi_is_double_dash(argv[i]))
		i++;
	*idx = i;
	return (0);
}

static int	cd_home(t_env **penv)
{
	const char	*home;

	home = env_get(*penv, "HOME");
	if (home == NULL)
	{
		bi_print_err("cd", "HOME not set", NULL);
		return (1);
	}
	return (change_dir_and_update_env(home, penv));
}

static int	cd_oldpwd(t_env **penv)
{
	const char	*oldpwd;

	oldpwd = env_get(*penv, "OLDPWD");
	if (oldpwd == NULL)
	{
		bi_print_err("cd", "OLDPWD not set", NULL);
		return (1);
	}
	if (change_dir_and_update_env(oldpwd, penv) != 0)
		return (1);
	printf("%s\n", env_get(*penv, "PWD"));
	return (0);
}

int	builtin_cd(char *const *argv, t_env **penv)
{
	const char	*arg;
	int			i;
	int			rc;

	i = 1;
	rc = cd_parse_options(argv, &i);
	if (rc != 0)
		return (rc);
	arg = argv[i];
	if (argv[i] != NULL && argv[i + 1] != NULL)
	{
		bi_print_err("cd", "too many arguments", NULL);
		return (1);
	}
	if (arg == NULL)
		return (cd_home(penv));
	if (ft_strcmp(arg, "-") == 0)
		return (cd_oldpwd(penv));
	return (change_dir_and_update_env(arg, penv));
}
