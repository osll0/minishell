/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_stage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:32:03 by seokson           #+#    #+#             */
/*   Updated: 2025/10/18 17:42:23 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exec.h"
#include "pipe.h"
#include "fd_utils.h"
#include "minishell_signal.h"

static int	handle_fork_error(t_pipe *p, int need_pipe, int pipe[2])
{
	int		i;
	int		err;

	err = errno;
	ex_print_err("fork", strerror(err));
	i = p->made;
	while (i-- > 0)
		(void)waitpid(-1, 0, 0);
	if (p->prev_in >= 0)
	{
		x_close(p->prev_in);
		p->prev_in = -1;
	}
	if (need_pipe)
	{
		x_close(pipe[0]);
		x_close(pipe[1]);
	}
	p->made = 0;
	p->last_pid = -1;
	return (1);
}

static void	setup_child_fds(t_pipe *p, int need_pipe, int pipe[2])
{
	if (p->prev_in >= 0)
	{
		x_dup2(p->prev_in, STDIN_FILENO);
		x_close(p->prev_in);
	}
	if (need_pipe)
	{
		x_dup2(pipe[1], STDOUT_FILENO);
		x_close(pipe[0]);
		x_close(pipe[1]);
	}
}

static void	setup_parent_fds(t_pipe *p, int need_pipe, int pipe[2], pid_t pid)
{
	if (p->prev_in >= 0)
	{
		x_close(p->prev_in);
		p->prev_in = -1;
	}
	if (need_pipe)
	{
		x_close(pipe[1]);
		p->prev_in = pipe[0];
	}
	p->last_pid = pid;
	p->made += 1;
	p->remain -= 1;
}

int	spawn_stage(const t_cmd *cmd, t_pipe *p, int need_pipe, const t_ast *ast)
{
	int		pipe[2];
	pid_t	pid;

	if (need_pipe && x_pipe(pipe) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (handle_fork_error(p, need_pipe, pipe));
	if (pid == 0)
	{
		setup_child_fds(p, need_pipe, pipe);
		child_exec(cmd, p->env, ast);
	}
	setup_parent_fds(p, need_pipe, pipe, pid);
	return (0);
}
