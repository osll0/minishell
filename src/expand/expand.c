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
#include "ast.h"
#include "loop.h"
#include "libft.h"

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

static void	process_quotes_here(const char *word, int *i, char **res)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
			append_char(res, word[(*i)++]);
	if (word[*i] == quote)
		(*i)++;
}

char	*expand_heredoc(const char *word, t_redir *r)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			process_quotes_here(word, &i, &res);
			r->quoted = 1;
		}
		else
			append_char(&res, word[i++]);
	}
	return (res);
}

int	check_ambig(const char *word, t_ctx *ctx)
{
	int			i;

	i = 0;
	printf("fuck1\n");
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			process_quotes_redir(word, &i);
		else if (word[i] == '$' && word[i + 1])
		{
			if (!process_dollar_redir(word, &i, ctx))
				return (1);
		}
		else
			i++;
	}
	printf("fuck\n");
	return (0);
}