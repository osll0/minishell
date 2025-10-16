/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:59:54 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/16 23:58:33 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"


void    expand(t_token *tokens, t_ctx *ctx)
{
	t_token *cur;
	char    *expanded;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD)
		{
			expanded = expand_word(cur->value, ctx);
			free(cur->value);
			cur->value = expanded;
		}
		cur = cur->next;
	}
}
