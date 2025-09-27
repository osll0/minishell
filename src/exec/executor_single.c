/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:28:29 by seokson           #+#    #+#             */
/*   Updated: 2025/09/10 13:40:45 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "exec.h"
#include "ast.h"

static int	wait_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_single_cmd(const t_cmd *cmd, t_env *env)
{
	pid_t		pid;
	t_builtin	bk;

	if (!cmd || cmd->argc == 0 || !cmd->argv || !cmd->argv[0])
		return (0);
	bk = builtin_lookup(cmd->argv[0]);
	if (bk == BUILTIN_CD || bk == BUILTIN_EXPORT
		|| BUILTIN_UNSET || BUILTIN_EXIT)
		return (run_builtin_parent_with_redirs(cmd, env));
//		return (builtin_exec_parent(bk, cmd->argv, env));
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_exec(cmd, env);
	return (wait_status(pid));
}
