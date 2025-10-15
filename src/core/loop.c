/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/14 17:06:30 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "loop.h"
#include "minishell_signal.h"
#include "env.h"
#include <unistd.h>
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include "exec.h"

void	free_loop(char *line, t_token *tokens, t_ast *ast)
{
	if (line)
		free(line);
	if (tokens)
		free_tokens(tokens);
	if (ast)
		free_ast(ast);
}

void	loop(t_env *env_list)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

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
		tokens = tokenize_input(line);
		ast = parse_tokens(tokens);
		print_ast(ast, 0);
		execute_ast(ast, env_list);
		free_loop(line, tokens, ast);
	}	
}
