/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:50:32 by seokson           #+#    #+#             */
/*   Updated: 2025/09/15 19:55:12 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "fd_utils.h"
#include "builtin.h"
#include "exec.h"

static int	backup_stdio(int save[2])
{
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	if (save[0] < 0 || save[1] < 0)
	{
		if (save[0] >= 0)
			x_close(save[0]);
		if (save[1] >= 0)
			x_close(save[1]);
		perror("minishell: dup");
		return (1);
	}
	return (0);
}

static void	restore_stdio(int save[2])
{
	if (save[0] >= 0)
	{
		x_dup2(save[0], STDIN_FILENO);
		x_close(save[0]);
	}
	if (save[1] >= 0)
	{
		x_dup2(save[1], STDOUT_FILENO);
		x_close(save[1]);
	}
}

int	run_builtin_parent_with_redirs(const t_cmd *cmd, t_env *env)
{
	int	save[2];
	int	rc;

	if (backup_stdio(save) != 0)
		return (1);
	if (apply_redirs(cmd->redirs, cmd->n_redirs) < 0)
	{
		restore_stdio(save);
		return (1);
	}
	rc = builtin_exec_parent(builtin_lookup(cmd->argv[0]),
			cmd->argv, env);
	restore_stdio(save);
	return (rc);
}
