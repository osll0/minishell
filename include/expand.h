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

void	expand(t_token *tokens, t_ctx *ctx);
char	*expand_word(const char *word, t_ctx *ctx);
# endif
