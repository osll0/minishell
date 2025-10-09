/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:24:17 by seokson           #+#    #+#             */
/*   Updated: 2025/10/07 14:24:59 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno-base.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "exec.h"

int	exec_with_sh(char **argv, char **envp, const char *file)
{
	int		i;
	int		rc;
	int		argc;
	char	**nv;

	i = 0;
	argc = 0;
	while (argv && argv[argc])
		argc++;
	nv = (char **)ft_calloc((size_t)argc + 2, sizeof(char *));
	if (!nv)
		return (1);
	nv[0] = (char *)"sh";
	nv[1] = (char *)file;
	i = 1;
	while (i < argc)
	{
		nv[i + 1] = argv[i];
		i++;
	}
	execve("/bin/sh", nv, envp);
	rc = ex_errno_code(errno);
	free(nv);
	return (rc);
}

static int	ex_prio(int e)
{
	if (e == EACCES)
		return (3);
	if (e == EISDIR)
		return (2);
	if (e == ELOOP)
		return (1);
	return (0);
}

int	ex_path_err_reduce(int acc, int now_err)
{
	int	pa;
	int	pn;

	pa = ex_prio(acc);
	pn = ex_prio(now_err);
	if (pn > pa)
		return (now_err);
	if (pa > 0)
		return (acc);
	if (acc == ENOENT)
		return (now_err);
	return (acc);
}

int	ex_path_err_finalize(int acc, int last_err)
{
	int	pr;

	pr = ex_prio(acc);
	if (pr > 0)
		return (acc);
	return (last_err);
}
