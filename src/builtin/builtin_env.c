/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:33:30 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 17:36:24 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

int	builtin_env(char **argv, t_env *env)
{
	t_env	*cur;

	if (argv[1])
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("env: usage: pwd [no options] [no arguments]\n", 2);
		return (2);
	}
	cur = env;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}
