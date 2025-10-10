/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/10 20:52:27 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "loop.h"
#include "minishell_signal.h"
#include "env.h"
#include <unistd.h>
#include "lexer.h"
#include <stdio.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("%s\n", tokens->value);
		tokens = tokens->next;
	}
}

void	loop(t_env *env_list)
{
	char	*line;

	(void)env_list;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (*line)
			add_history(line);
		print_tokens(tokenize_input(line));
		free(line);
	}	
}
