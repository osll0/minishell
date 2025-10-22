/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:37:18 by seokson           #+#    #+#             */
/*   Updated: 2025/10/22 11:40:23 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env.h"
#include "builtin.h"

static int	unset_check_options(char *const *argv, int *idx)
{
	int	i;

	i = *idx;
	if (argv[i] == NULL)
		return (0);
	if (bi_is_double_dash(argv[i]))
	{
		*idx = i + 1;
		return (0);
	}
	if (argv[i][0] == '-' && argv[i][1] != '\0')
	{
		bi_print_err("unset", "invalid option", argv[i]);
		return (2);
	}
	return (0);
}

int	builtin_unset(char *const *argv, t_env **penv)
{
	int	i;
	int	rc;

	i = 1;
	rc = unset_check_options(argv, &i);
	if (rc != 0)
		return (rc);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			i++;
			continue ;
		}
		if (bi_is_valid_identifier(argv[i]))
			env_unset(penv, argv[i]);
		i++;
	}
	return (0);
}
