/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:41:45 by seunbaek          #+#    #+#             */
/*   Updated: 2025/09/21 12:46:15 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# include <signal.h>

extern volatile sig_atomic_t	g_interrupted;

void	sigint_handler_parent(int sig);
void	set_signals_parent(void);
void	set_signals_child(void);
#endif
