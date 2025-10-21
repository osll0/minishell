/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:32:49 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/21 08:32:50 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "heredoc.h"
#include "ast.h"
#include "env.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "context.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "expand.h"
#include "minishell_signal.h"

int	heredoc_parent(int fd[2], int pid, t_ctx *ctx)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	set_signals_parent();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (fd[0]);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		ctx->last_status = 130;
		close(fd[0]);
		return (-1);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		close(fd[0]);
		return (-1);
	}
}
