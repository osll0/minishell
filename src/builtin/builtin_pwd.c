/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:27:46 by seokson           #+#    #+#             */
/*   Updated: 2025/10/22 11:18:41 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "builtin.h"

static int	pwd_check_options(char **argv)
{
	if (!argv || !argv[1])
		return (0);
	if (bi_is_option_token(argv[1]))
	{
		bi_print_err("pwd", "invalid option", argv[1]);
		ft_putstr_fd("pwd: usage: pwd [no options]\n", 2);
		return (2);
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
	bi_print_err("pwd", strerror(errno), NULL);
	return (1);
}
