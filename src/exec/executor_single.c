/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:28:29 by seokson           #+#    #+#             */
/*   Updated: 2025/10/09 17:50:09 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin.h"
#include "ast.h"
#include "builtin.h"
#include "exec.h"
#include "minishell_signal.h"

static int	wait_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		ex_print_err("waitpid", strerror(errno));
		set_signals_parent();
		check_fork_signal(status);
		return (1);
	}
	set_signals_parent();
	check_fork_signal(status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_single_cmd(const t_cmd *cmd, t_env **penv)
{
	pid_t		pid;
	t_builtin	bk;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	bk = builtin_lookup(cmd->argv[0]);
	if (bk == BUILTIN_CD || bk == BUILTIN_EXPORT
		|| bk == BUILTIN_UNSET || bk == BUILTIN_EXIT)
		return (run_builtin_parent_with_redirs(cmd, penv));
	set_signals_fork();
	pid = fork();
	if (pid < 0)
	{
		set_signals_parent();
		ex_print_err("fork", strerror(errno));
		return (1);
	}
	if (pid == 0)
		child_exec(cmd, *penv);
	return (wait_status(pid));
}
