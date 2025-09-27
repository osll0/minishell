/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:17:02 by seokson           #+#    #+#             */
/*   Updated: 2025/09/27 17:41:57 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"

static void	set_exit_status(int *do_exit, int *exit_status, int d, int e)
{
	*do_exit = d;
	*exit_status = e;
}

static int	exit_check_options(const char *arg, long long *out, int *d, int *e)
{
	int			overflow;
	long long	v;

	if ((bi_is_single_dash(arg) || bi_is_triple_dash(arg))
		|| (!bi_parse_longlong(arg, &v, &overflow) || overflow))
	{
		set_exit_status(d, e, 1, 2);
		bi_print_err("exit", "numeric argument required", arg);
		return (2);
	}
	*out = v;
	return (0);
}

/*
 * exit_status 변수 받지않고 그냥 return value로 exit?
*/
int	builtin_exit(char *const *argv, int *do_exit, int *exit_status)
{
	int			i;
	int			rc;
	long long	v;

	set_exit_status(do_exit, exit_status, 0, 0);
	i = 1;
	if (argv[i] && bi_is_double_dash(argv[i]))
		i++;
	if (argv[i] == NULL)
	{
		set_exit_status(do_exit, exit_status, 1, 0);
		return (0);
	}
	rc = exit_check_options(argv[i], &v, do_exit, exit_status);
	if (rc != 0)
		return (rc);
	if (argv[i + 1] != NULL)
	{
		set_exit_status(do_exit, exit_status, 0, 1);
		bi_print_err("exit", "too many arguments", NULL);
		return (1);
	}
	set_exit_status(do_exit, exit_status, 1, (int)(unsigned char)(v & 0xFF));
	return (0);
}
