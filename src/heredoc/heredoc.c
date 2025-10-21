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

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "heredoc.h"
#include "ast.h"
#include "env.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "context.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "expand.h"
#include "minishell_signal.h"

int	process_heredocs(t_ast *ast, t_ctx *ctx)
{
	int		i;
	t_redir	*r;

	i = 0;
	if (!ast)
		return (1);
	if (ast->type == N_CMD)
	{
		while (i < ast->cmd.n_redirs)
		{
			r = &ast->cmd.redirs[i];
			if (r->kind == R_HERE)
			{
				r->here_fd = handle_heredoc(r->target, r->quoted, ctx, ast);
				if (r->here_fd < 0)
					return (0);
			}
			i++;
		}
	}
	else if (ast->type == N_PIPE)
		if (!process_heredocs(ast->left, ctx)
			|| !process_heredocs(ast->right, ctx))
			return (0);
	return (1);
}

char	*expand_quoted(char *word, t_ctx *ctx)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1])
			process_dollar(word, &i, &res, ctx);
		else
			append_char(&res, word[i++]);
	}
	free(word);
	return (res);
}

int	handle_heredoc(char *delimiter, int quoted, t_ctx *ctx, t_ast *ast)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	set_signals_fork();
	pid = fork();
	if (pid < 0)
	{
		set_signals_parent();
		return (close(fd[0]), close(fd[1]), -1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		set_signals_here();
		run_heredoc_loop(delimiter, quoted, ctx, fd[1]);
		free_ast(ast);
		env_free(&ctx->env);
		close(fd[1]);
		exit(0);
	}
	else
		return (heredoc_parent(fd, pid, ctx));
}

static void	warn_heredoc_eof(const char *delimiter)
{
	const char	*prefix;
	const char	*suffix;

	prefix = "bash: 경고: here-document가 1번 행에서 파일의 끝으로 구분함 (`";
	suffix = "'아(가) 필요함)\n";
	write(STDERR_FILENO, prefix, strlen(prefix));
	write(STDERR_FILENO, delimiter, strlen(delimiter));
	write(STDERR_FILENO, suffix, strlen(suffix));
}

void	run_heredoc_loop(char *delimiter, int quoted, t_ctx *ctx, int out_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			warn_heredoc_eof(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!quoted)
		{
			line = expand_quoted(line, ctx);
		}
		ft_putendl_fd(line, out_fd);
		free(line);
	}
}
