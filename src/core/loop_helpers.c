/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 01:35:51 by seokson           #+#    #+#             */
/*   Updated: 2025/10/18 13:04:09 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parser.h"
#include "lexer.h"
#include "expand.h"
#include "exec.h"
#include "libft.h"
#include "prompt.h"
#include "loop.h"
#include "minishell_signal.h"

void	update_exit_status_by_signal(t_ctx *ctx)
{	
	if (g_exit_status == 1)
	{
		ctx->last_status = 130;
		g_exit_status = 0;
	}
	
}

void	free_loop(char *line, t_token *tokens, t_ast *ast)
{
	if (line)
		free(line);
	if (tokens)
		free_tokens(tokens);
	if (ast)
		free_ast(ast);
}

int	prompt_readline(t_ctx *ctx, char **out_line)
{
	char *prompt;

	prompt = make_prompt(ctx);
	// *out_line = readline(prompt);
	*out_line = get_next_line(0);
	update_exit_status_by_signal(ctx);
	free(prompt);
	if (!*out_line)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	// if (**out_line)
	// 	add_history(*out_line);
	return (0);
}

int	tokenize_or_continue(char *line, t_token **out_tokens)
{
	*out_tokens = tokenize_input(line);
	if (!*out_tokens)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	if_exit(int status, char *line, t_token *toks, t_ast *ast, t_ctx *ctx)
{
	int	code;

	if (status >= 256)
	{
		code = (unsigned char)(status - 256);
		free_loop(line, toks, ast);
		rl_clear_history();
		env_free(&ctx->env);
		exit(code);
	}
	if (*line)
		add_history(line);
}
