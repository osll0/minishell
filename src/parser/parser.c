/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:40:45 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/14 17:05:12 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "context.h"
#include <stdlib.h>
#include <stdio.h>
#include "expand.h"

t_ast	*parse_tokens(t_token *tokens, t_ctx *ctx)
{
	t_token	*cur;

	cur = tokens;
	return (parse_pipe_sequence(&cur, ctx));
}

t_ast	*parse_pipe_sequence(t_token **cur, t_ctx *ctx)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_command(cur, ctx);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command(cur, ctx);
		if (!right)
			break ;
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->type = N_PIPE;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

void	parse_tokens_to_cmd(t_token **cur, t_cmd *cmd, t_ctx *ctx)
{
	while (*cur && (*cur)->type != TOKEN_PIPE)
	{
		if ((*cur)->type == TOKEN_WORD)
			cmd->argv[cmd->argc++] = expand_word((*cur)->value, ctx);
		else if ((*cur)->type >= 2 && (*cur)->type <= 5)
			cmd->redirs[cmd->n_redirs++] = parse_redir(cur, ctx);
		if (*cur)
			*cur = (*cur)->next;
	}
	cmd->argv[cmd->argc] = NULL;
}

t_ast	*parse_command(t_token **cur, t_ctx *ctx)
{
	t_cmd	cmd;
	t_ast	*node;

	cmd = init_cmd();
	cmd.argv = malloc(sizeof(char *) * 256);
	cmd.redirs = malloc(sizeof(t_redir) * 16);
	if (!cmd.argv || !cmd.redirs)
		return (NULL);
	parse_tokens_to_cmd(cur, &cmd, ctx);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = N_CMD;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redir	parse_redir(t_token **cur, t_ctx *ctx)
{
	t_redir	r;
	t_token	*tok;

	tok = *cur;
	if (tok->type == TOKEN_REDIR_IN)
		r.kind = R_IN;
	else if (tok->type == TOKEN_REDIR_OUT)
		r.kind = R_OUT;
	else if (tok->type == TOKEN_REDIR_APPEND)
		r.kind = R_APP;
	else
		r.kind = R_HERE;
	*cur = (*cur)->next;
	if (*cur && (*cur)->type == TOKEN_WORD)
		fill_redir(&r, (*cur)->value, ctx);
	else
		r.target = NULL;
	return (r);
}
