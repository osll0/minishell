/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 05:15:51 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 05:15:52 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "ast.h"
# include "context.h"

int     heredoc_parent(int fd[2], int pid, t_ctx *ctx);
int     process_heredocs(t_ast *ast, t_ctx *ctx);
int	    handle_heredoc(char *delimiter, int quoted, t_ctx *ctx, t_ast *ast);
void	run_heredoc_loop(char *delimiter, int quoted, t_ctx *ctx, int out_fd);
# endif