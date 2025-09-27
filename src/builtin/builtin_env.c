/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:33:30 by seokson           #+#    #+#             */
/*   Updated: 2025/09/21 16:59:35 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static int	env_check_options(char **argv)
{
	int	i;

	i = 1;
	if (argv[i] && (bi_is_triple_dash(argv[i]) || bi_is_option_token(argv[i])))
	{
		bi_print_err("env", "invalid option", argv[1]);
		ft_putstr_fd("env: usage: env [no options] [no arguments]\n", 2);
		return (2);
	}
	if (argv[i] && bi_is_double_dash(argv[i]))
		i++;
	if (argv[i] != NULL)
	{
		bi_print_err("env", "invalid option", argv[i]);
		ft_putstr_fd("env: usage: env [no options] [no arguments]\n", 2);
		return (2);
	}
	return (0);
}

int	builtin_env(char **argv, t_env *env)
{
	int		rc;
	t_env	*cur;

	if (argv[1] && bi_is_single_dash(argv[1]))
		return (0);
	rc = env_check_options(argv);
	if (rc != 0)
		return (rc);
	cur = env;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}
