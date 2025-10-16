/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/17 00:15:57 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "loop.h"
#include "minishell_signal.h"
#include "env.h"
#include "context.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include "exec.h"
#include "expand.h"
#include "libft.h"

static void	free_loop(char *line, t_token *tokens, t_ast *ast)
{
	if (line)
		free(line);
	if (tokens)
		free_tokens(tokens);
	if (ast)
		free_ast(ast);
}

int	loop(t_ctx *ctx)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;
	int		last_status;

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
			free_loop(line, tokens, NULL);
			continue ;
		}
		expand(tokens, ctx);
		ast = parse_tokens(tokens);
		last_status = execute_ast(ast, &ctx->env);
		ctx->last_status = last_status;
		free_loop(line, tokens, ast);
	}	
	return (ctx->last_status);
}
