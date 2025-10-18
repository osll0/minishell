/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:45:04 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 19:45:05 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "minishell_signal.h"
#include <stdio.h>
#include "context.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	heredoc_status = 1;
}

void	set_signals_heredoc(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	update_exit_status_by_here(t_ctx *ctx)
{	
	if (heredoc_status == 1)
	{
		ctx->last_status = 130;
		heredoc_status = 0;
	}
	
}