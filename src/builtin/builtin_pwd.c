/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:27:46 by seokson           #+#    #+#             */
/*   Updated: 2025/09/21 16:54:10 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static int	pwd_check_options(char **argv)
{
	int	i;

	i = 1;
	while (argv && argv[i])
	{
		if (bi_is_triple_dash(argv[i]))
		{
			bi_print_err("pwd", "invalid option", argv[i]);
			ft_putstr_fd("pwd: usage: pwd [no options]\n", 2);
			return (2);
		}
		if (!bi_is_single_dash(argv[i]) && !bi_is_double_dash(argv[i]))
		{
			bi_print_err("pwd", "invalid option", argv[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int	builtin_pwd(char **argv)
{
	int		rc;
	char	buf[4096];

	rc = pwd_check_options(argv);
	if (rc != 0)
		return (rc);
	if (getcwd(buf, sizeof(buf)))
	{
		printf("%s\n", buf);
		return (0);
	}
	perror("pwd");
	return (1);
}
