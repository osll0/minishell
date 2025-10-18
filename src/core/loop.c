/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:09:08 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 12:33:37 by seokson          ###   ########.fr       */
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
#include "heredoc.h"

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
		if (setup_redir(tokens, ctx) == 0)
		{
			free_loop(line, tokens, NULL);
			continue;
		}
		ast = parse_tokens(tokens, ctx);
		free_tokens(tokens);
		process_heredocs(ast, ctx);
		rc = execute_ast(ast, &ctx->env);
		if_exit(rc, line, NULL, ast, ctx);
		ctx->last_status = rc;
		free_loop(line, NULL, ast);
	}
	return (ctx->last_status);
}
