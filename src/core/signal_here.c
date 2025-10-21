/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:43:50 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/21 08:43:52 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "minishell_signal.h"
#include <stdio.h>

void	set_signals_here(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
