/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:40:17 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/14 16:45:52 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "lexer.h"

t_ast   *parse_tokens(t_token *tokens);
t_ast   *parse_pipe_sequence(t_token **cur);
t_ast   *parse_command(t_token **cur);
t_cmd init_cmd(void);
t_redir parse_redir(t_token **cur);

void    free_ast(t_ast *node);
void    print_ast(t_ast *node, int depth);

#endif
