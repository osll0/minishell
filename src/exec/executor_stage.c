/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_stage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:32:03 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 18:41:51 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exec.h"
#include "pipe.h"
#include "fd_utils.h"

static int	handle_fork_error(t_pipe *p, int need_pipe, int pipe[2])
{
	perror("minishell:fork");
	while (p->made-- > 0)
		(void)waitpid(-1, 0, 0);
	if (p->prev_in >= 0)
		x_close(p->prev_in);
	if (need_pipe)
	{
		x_close(pipefd[0]);
		x_close(pipefd[1]);
	}
	return (1);
}

static void	setup_child_fds(t_pipe *p, int need_pipe, int pipe[2])
{
	if (p->prev_in >= 0)
		x_dup2(p->prev_in, STDIN_FILENO);
	if (need_pipe)
		x_dup2(pipe[1], STDOUT_FILENO);
	if (p->prev_in >= 0)
		x_close(p->prev_in);
	if (need_pipe)
	{
		x_close(pipefd[0]);
		x_close(pipefd[1]);
	}
}

static void	setup_parent_fds(t_pipe *p, int need_pipe, int pipe[2], pid_t pid)
{
	if (p->prev_in >= 0)
		x_close(p->prev_in);
	if (need_pipe)
		x_close(pipe[1]);
	if (need_pipe)
		p->prev_in = pipe[0];
	else
		p->prev_in = -1;
	p->last_pid = pid;
	p->made += 1;
	p->remain -= 1;
}

int	spawn_stage(const t_cmd *cmd, t_pipe *p, int need_pipe)
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
		child_exec(cmd, p->env);
	}
	setup_parent_fds(p, need_pipe, pipefd, pid);
	return (0);
}
