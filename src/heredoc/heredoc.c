/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 04:47:46 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 04:47:48 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "ast.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int process_heredocs(t_ast *ast)
{
	if (!ast)
		return (1);
	if (ast->type == N_CMD)
	{
		for (int i = 0; i < ast->cmd.n_redirs; i++)
		{
			t_redir *r = &ast->cmd.redirs[i];
			if (r->kind == R_HERE)
			{
				r->here_fd = handle_heredoc(r->target);
				if (r->here_fd < 0)
					return (0);
			}
		}
	}
	else if (ast->type == N_PIPE)
	{
		if (!process_heredocs(ast->left))
			return (0);
		if (!process_heredocs(ast->right))
			return (0);
	}
	return (1);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
