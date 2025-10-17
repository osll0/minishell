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

int process_heredocs(t_ast *ast);
int	handle_heredoc(char *delimiter);

# endif