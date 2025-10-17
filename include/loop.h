/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:47:24 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/17 02:18:17 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "ast.h"
# include "lexer.h"
# include "context.h"

void	free_loop(char *line, t_token *tokens, t_ast *ast);
int		prompt_readline(t_ctx *ctx, char **out_line);
int		tokenize_or_continue(char *line, t_token **out_tokens);
void	if_exit(int status, char *line, t_token *toks, t_ast *ast, t_ctx *ctx);
void	update_exit_status_by_signal(t_ctx *ctx);
int		loop(t_ctx *ctx);
int     setup_redir(t_ast *node, t_ctx *ctx);
#endif
