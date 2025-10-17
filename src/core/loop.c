/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/17 02:17:02 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_signal.h"
#include "env.h"
#include "parser.h"
#include <stdio.h>
#include "exec.h"
#include "expand.h"
#include "libft.h"
#include "loop.h"

int	loop(t_ctx *ctx)
{
	int		rc;
	char	*line;
	t_ast	*ast;
	t_token	*tokens;

	while (1)
	{
		if (prompt_readline(ctx, &line))
			break ;
		if (tokenize_or_continue(line, &tokens))
			continue ;
		expand(tokens, ctx);
		ast = parse_tokens(tokens);
		if (setup_redir(ast, ctx) == 0)
		{
			free_loop(line, tokens, ast);
			continue ;
		}
		rc = execute_ast(ast, &ctx->env);
		ctx->last_status = rc;
		if_exit(rc, line, tokens, ast, ctx);
		free_loop(line, tokens, ast);
	}
	return (ctx->last_status);
}
