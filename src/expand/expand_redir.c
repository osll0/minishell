/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:39:44 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 17:39:48 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "loop.h"

int	process_dollar_redir(const char *word, int *i, t_ctx *ctx)
{
	int		start;
	char	*key;
	char	*val;

	(*i)++;
	start = *i;
	if (word[*i] != '?')
		while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
			(*i)++;
	else
		(*i)++;
	key = ft_substr(word, start, *i - start);
	val = expand_env_value(key, ctx);
	start = has_space(val);
	free(key);
	free(val);
	return (start);
}

void	process_quotes_redir(const char *word, int *i)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
		(*i)++;
	if (word[*i] == quote)
		(*i)++;
}