/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:30:02 by seokson           #+#    #+#             */
/*   Updated: 2025/09/27 16:24:08 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "builtin.h"

static int	free_and_ret1(char *key)
{
	free(key);
	return (1);
}

static int	export_one(t_env **penv, const char *arg)
{
	const char	*eq;
	char		*key;
	char		*value;
	int			rc;

	eq = ft_strchr(arg, '=');
	if (eq == NULL)
	{
		if (!bi_is_valid_identifier(arg))
			return (1);
		return (env_set(penv, arg, NULL) == -1);
	}
	key = ft_strndup(arg, (size_t)(eq - arg));
	if (key == NULL)
		return (1);
	if (!bi_is_valid_identifier(key))
		return (free_and_ret1(key));
	value = ft_strdup(eq + 1);
	if (!value && *(eq + 1) != '\0')
		return (free_and_ret1(key));
	rc = env_set(penv, key, value);
	free(key);
	free(value);
	return (rc == -1);
}

int	print_export(t_env *env)
{
	int		i;
	char	*eq;
	char	**arr;

	arr = env_to_array(env);
	if (arr == NULL)
		return (0);
	bi_strtab_sort(arr);
	i = 0;
	while (arr[i] != NULL)
	{
		eq = ft_strchr(arr[i], '=');
		if (eq != NULL)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", arr[i], eq + 1);
			*eq = '=';
		}
		else
			printf("declare -x %s\n", arr[i]);
		i++;
	}
	free_env_array(arr);
	return (0);
}

static int	check_options(char *const *argv, t_env **penv, int *pi)
{
	if (bi_is_double_dash(argv[*pi]))
	{
		(*pi)++;
		if (argv[*pi] == NULL)
		{
			print_export(*penv);
			return (3);
		}
	}
	else
	{
		if (bi_is_single_dash(argv[*pi]))
		{
			bi_print_err("export", "not a valid identifier", argv[*pi]);
			return (1);
		}
		if (bi_is_triple_dash(argv[*pi]) || bi_is_option_token(argv[*pi]))
		{
			bi_print_err("export", "invalid option", argv[*pi]);
			ft_putstr_fd("export: usage: export [no options]\n", 2);
			return (2);
		}
	}
	return (0);
}

int	builtin_export(char *const *argv, t_env **penv)
{
	int	i;
	int	rc;

	i = 1;
	rc = 0;
	if (argv[i] == NULL)
		return (print_export(*penv));
	rc = check_options(argv, penv, &i);
	if (rc == 3)
		return (0);
	if (rc != 0)
		return (rc);
	while (argv[i] != NULL)
	{
		if (export_one(penv, argv[i]) != 0)
		{
			bi_print_err("export", "not a valid identifier", argv[i]);
			rc = 1;
		}
		i++;
	}
	return (rc);
}
