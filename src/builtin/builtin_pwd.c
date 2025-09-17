/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:27:46 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 17:47:53 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static int	pwd_check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv && argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if (ft_strcmp(argv[i], "--") == 0)
				break;
			ft_putstr_fd("minishell: pwd:", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("pwd: usage: pwd [no options]\n", 2);
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

	rc = pwd_check_args(argv);
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
