/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:13:40 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/16 23:56:48 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "context.h"
# include "lexer.h"
# include "ast.h"

void	process_quotes_redir(const char *word, int *i);
void	expand(t_token *tokens, t_ctx *ctx);
char	*expand_word(const char *word, t_ctx *ctx);
char	*expand_heredoc(const char *word, t_redir *r);
char	*expand_env_value(const char *key, t_ctx *ctx);
int	    check_ambig(const char *s, t_ctx *ctx);
int	    process_dollar_redir(const char *word, int *i, t_ctx *ctx);
void	append_char(char **res, char c);
void	process_dollar(const char *word, int *i, char **res, t_ctx *ctx);

# endif
