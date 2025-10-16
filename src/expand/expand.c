/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:59:54 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/16 16:59:56 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "lexer.h"
#include <stdlib.h>


void    expand(t_token *tokens, t_env *env)
{
	t_token *cur;
	char    *expanded;

	cur = tokens;
	while(cur)
	{
		if (cur->type == TOKEN_WORD)
		{
			expanded = expand_word(cur->value, env);
			free(cur->value);
			cur->value = expanded;
		}
		cur = cur->next;
	}
}