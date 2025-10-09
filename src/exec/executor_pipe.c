/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:08:07 by seokson           #+#    #+#             */
/*   Updated: 2025/10/05 17:12:19 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "fd_utils.h"
#include "ast.h"
#include "exec.h"

static int	count_cmds(const t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == N_CMD)
		return (1);
	return (count_cmds(ast->left) + count_cmds(ast->right));
}

static int	decode_wait_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	wait_all(int k, pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 1;
	while (k > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
		{
			if (errno == EINTR)
				continue ;
			if (errno == ECHILD)
				break ;
			ex_print_err("waitpid", strerror(errno));
			break ;
		}
		else if (pid == last_pid)
			last_status = decode_wait_status(status);
		k--;
	}
	return (last_status);
}

static int	exec_pipeline_dfs(const t_ast *n, t_pipe *p)
{
	int	rc;
	int	need_pipe;

	if (!n)
		return (0);
	if (n->type == N_CMD)
	{
		need_pipe = (p->remain > 1);
		return (spawn_stage(&n->cmd, p, need_pipe));
	}
	rc = exec_pipeline_dfs(n->left, p);
	if (rc != 0)
		return (rc);
	return (exec_pipeline_dfs(n->right, p));
}

int	execute_pipe(const t_ast *node, t_env **penv)
{
	int		rc;
	t_pipe	ctx;

	if (!node)
		return (0);
	ctx.prev_in = -1;
	ctx.made = 0;
	ctx.last_pid = -1;
	ctx.env = *penv;
	ctx.remain = count_cmds(node);
	if (ctx.remain <= 0)
		return (0);
	rc = exec_pipeline_dfs(node, &ctx);
	if (ctx.prev_in >= 0)
		x_close(ctx.prev_in);
	if (rc != 0)
		return (rc);
	return (wait_all(ctx.made, ctx.last_pid));
}
