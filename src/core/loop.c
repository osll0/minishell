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
#include "expand.h"
#include "libft.h"

static void	set_exit(int status, t_env *env)
{
	env_set(&env, "?", ft_itoa(status));
}

static void	free_loop(char *line, t_token *tokens, t_ast *ast)
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

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		tokens = tokenize_input(line);
		if (!tokens)
		{
			free_loop(line, tokens, 0);
			continue ;
		}
		expand(tokens, env_list);
		ast = parse_tokens(tokens);
		set_exit(execute_ast(ast, &env_list), env_list);
		free_loop(line, tokens, ast);
	}	
}
