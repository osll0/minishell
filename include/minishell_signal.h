/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:41:45 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/10 19:38:25 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H
# include <signal.h>

extern volatile sig_atomic_t	g_interrupted;

void	sigint_handler_parent(int sig);
void	set_signals_parent(void);
void	set_signals_child(void);
#endif
