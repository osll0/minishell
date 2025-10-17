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

void	set_ambig(t_redir *r, t_token *cur)
{
	r->ambig = 1;
	if (cur)
		r->target = ft_strdup(cur->value);
	else
		r->target = ft_strdup("'\\n'");
}