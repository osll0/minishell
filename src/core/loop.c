/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/09/21 13:06:33 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "loop.h"
#include "signal.h"

void	loop(t_env *env_list)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (g_interrupted)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			re_redisplay();
			g_interrupted = 0;
			continue ;
		}
		if (!line)
		{
			break ;
		}
		if (*line)
			add_history(line);
		todo_parse();
		free(line);
	}
}
