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
#include "libft.h"
#include <unistd.h>

int	redir_error(const char *msg, const char *near, t_ctx *ctx)
{
	write(2, msg, ft_strlen(msg));
	write(2, "'", 1);
	write(2, near, ft_strlen(near));
	write(2, "'", 1);
	write(2, "\n", 1);
	ctx->last_status = 2;
	return (0);
}

int	has_space(const char *s)
{
	while (*s)
	{
		if (ft_isspace(*s))
			return (0);
		s++;
	}
	return (1);
}



int	setup_redir(t_token *node, t_ctx *ctx)
{
	while (node)
	{
		if (1 <= node->type && node->type <= 5)
		{
			if (node->type == TOKEN_PIPE)
			{
				if (!node->next)
					return (redir_error("parse error near ", "|", ctx));
			}
			else if (2 <= node->type && node->type <= 5)
			{
					if (!node->next)
						return (redir_error("parse error near ", "\\n", ctx));
					else if(node->next->type != TOKEN_WORD)
						return (redir_error("parse error near ", node->next->value, ctx));
			}
		}
		node = node->next;		
	}
	return (1);
}
