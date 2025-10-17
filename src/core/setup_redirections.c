/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:06:52 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/17 20:06:55 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "lexer.h"

int	check_redir(t_ast *node, t_ctx *ctx)
{
	t_redir		*r;
	int			i;

	i = 0;
	while (i < node->cmd.n_redirs)
	{
		r = &node->cmd.redirs[i];
		if (r->ambig)
		{
			lexer_error("parse error near ", r->target);
			ctx->last_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

int	setup_redir(t_ast *node, t_ctx *ctx)
{
	if (!node)
		return (0);
	if (node->type == N_CMD)
		return (check_redir(node, ctx));
	else if (node->type == N_PIPE)
	{
		if (!node->left->cmd.argv[0] || !node->right->cmd.argv[0])
		{
			lexer_error("parse error near ", "\'|\'");
			ctx->last_status = 2;
			return (0);
		}
		if (!setup_redir(node->left, ctx))
			return (0);
		if (!setup_redir(node->right, ctx))
			return (0);
	}
	return (1);
}