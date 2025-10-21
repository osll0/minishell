/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:41:45 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/10 20:54:46 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H
# include <signal.h>
# include "context.h"

extern int	g_exit_status;

void	sigint_handler_parent(int sig);
void	set_signals_parent(void);
void	set_signals_child(void);
void	set_signals_fork(void);
void    check_fork_signal(int stat);
void	set_signals_here(void);

#endif
