/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:41:09 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/14 16:41:16 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "loop.h"
#include "context.h"
#include "expand.h"
#include <stdlib.h>

static void	free_argv(t_ast *node)
{
	int	i;

	i = 0;
	while (i < node->cmd.argc)
	{
		free(node->cmd.argv[i]);
		i++;
	}
	free(node->cmd.argv);
}

static void	free_redirs(t_ast *node)
{
	int	i;

	i = 0;
	while (i < node->cmd.n_redirs)
	{
		free(node->cmd.redirs[i].target);
		i++;
	}
	free(node->cmd.redirs);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	if (node->type == N_CMD)
	{
		free_argv(node);
		free_redirs(node);
	}
	free(node);
}

t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.argv = 0;
	cmd.redirs = 0;
	cmd.argc = 0;
	cmd.n_redirs = 0;
	return (cmd);
}

void	fill_redir(t_redir *r, const char *s, t_ctx *ctx)
{
	r->here_fd = -1;
	r->quoted = 0;
	r->ambig = 0;
	if (r->kind == TOKEN_HEREDOC)
	{
		r->target = expand_heredoc(s, r);
	}
	else
	{
		if (check_ambig(s, ctx))
		{
			r->ambig = 1;
			r->target = ft_strdup(s);
		}
		else
			r->target = expand_word(s, ctx);
	}
}