/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:48:50 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/10 20:55:01 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "minishell_signal.h"
#include <stdio.h>

int	g_exit_status = 0;
int	heredoc_status = 0;

void	sigint_handler_parent(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	set_signals_parent(void)
{
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	check_fork_signal(int stat)
{
	if ((stat & 255) != 0)
	{
		if ((stat & 127) == 2)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if((stat & 127) == 3)
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	}
}