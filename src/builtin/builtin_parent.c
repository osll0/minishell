/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:00:17 by seokson           #+#    #+#             */
/*   Updated: 2025/10/05 13:55:15 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

static int	will_exit(char *const *argv)
{
	int			i;
	int			overflow;
	long long	v;

	i = 1;
	if (argv[i] && bi_is_double_dash(argv[i]))
		i++;
	if (argv[i] == NULL)
		return (1);
	if (argv[i + 1] != NULL)
		return (0);
	if (bi_is_single_dash(argv[i]) || bi_is_triple_dash(argv[i]))
		return (1);
	if (!bi_parse_longlong(argv[i], &v, &overflow) || overflow)
		return (1);
	return (1);
}

int	builtin_exec_parent(t_builtin k, char **argv, t_env **penv)
{
	int	do_exit;
	int	exit_status;
	int	rc;

	if (!argv || !argv[0])
		return (0);
	if (k == BUILTIN_CD)
		return (builtin_cd(argv, penv));
	if (k == BUILTIN_EXPORT)
		return (builtin_export(argv, penv));
	if (k == BUILTIN_UNSET)
		return (builtin_unset(argv, penv));
	if (k == BUILTIN_EXIT)
	{
		if (will_exit(argv))
			ft_putstr_fd("exit\n", 2);
		rc = builtin_exit(argv, &do_exit, &exit_status);
		if (do_exit)
			return (256 + (unsigned char)exit_status);
		return (rc);
	}
	return (0);
}
