/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:08:07 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 18:41:53 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "exec.h"
#include "fd_utils.h"
#include "ast.h"

static int	count_cmds(const t_ast *ast)
{
	int	count;

	if (!ast)
		return (0);
	if (ast->type == N_CMD)
		return (1);
	count = 0;
	count += count_cmds(ast->left, out, idx);
	count += count_cmds(ast->right, out, idx);
	return (count);
}

static int	wait_all(int k, pid_t last_pid)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	pid;

	i = 0;
	last_status = 1;
	while (i < k)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			perror("minishell: waitpid");
		else if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = 1;
		}
		i++;
	}
	return (last_status);
}

static int	exec_pipeline_dfs(const t_ast *n, t_pipe *p)
{
	int	need_pipe;

	if (!n)
		return (0);
	if (n->type == N_CMD)
	{
		need_pipe = 0;
		if (p->remain > 1)
			need_pipe = 1;
		return (spawn_stage(&n->cmd, p, need_pipe));
	}
	if (exec_pipeline_dfs(n->left, p) != 0)
		return (1);
	return (exec_pipeline_dfs(n->right, p));
}

int	execute_pipe(const t_ast *node, t_env *env)
{
	int		rc;
	t_pipe	ctx;

	if (!node)
		return (0);
	ctx.prev_in = -1;
	ctx.made = 0;
	ctx.last_pid = -1;
	ctx.env = env;
	ctx.remain = count_cmds(node);
	if (ctx.remain <= 0)
		return (0);
	rc = exec_pipeline_dfs(node, &ctx);
	if (ctx.prev_in >= 0)
		x_close(ctx.prev_in);
	if (rc != 0)
		return (1);
	return (wait_all(ctx.made, ctx.last_pid));
}
