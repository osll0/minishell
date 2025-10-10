/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:57:58 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/10 19:58:21 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

t_token	*free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

void	lexer_error(const char *msg, const char *near)
{
	write(2, msg, ft_strlen(msg));
	write(2, near, ft_strlen(near));
	write(2, "\n", 1);
}
