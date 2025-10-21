/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:00:21 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/17 00:16:58 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "env.h"
#include "libft.h"

char	*expand_env_value(const char *key, t_ctx *ctx)
{
	const char	*v;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(ctx->last_status));
	v = env_get(ctx->env, key);
	if (!v)
		return (ft_strdup(""));
	return (ft_strdup(v));
}

void	append_char(char **res, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(*res, tmp);
	free(*res);
	*res = joined;
}

void	process_dollar(const char *word, int *i, char **res, t_ctx *ctx)
{
	int		start;
	char	*key;
	char	*val;
	char	*joined;

	(*i)++;
	start = *i;
	if (word[*i] != '?')
		while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
			(*i)++;
	else
		(*i)++;
	key = ft_substr(word, start, *i - start);
	val = expand_env_value(key, ctx);
	free(key);
	joined = ft_strjoin(*res, val);
	free(*res);
	free(val);
	*res = joined;
}

static void	process_quotes(const char *word, int *i, char **res, t_ctx *ctx)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
	{
		if (quote == '"' && word[*i] == '$' && word[*i + 1])
			process_dollar(word, i, res, ctx);
		else
			append_char(res, word[(*i)++]);
	}
	if (word[*i] == quote)
		(*i)++;
}

char	*expand_word(const char *word, t_ctx *ctx)
{
	char	*res;
	int		i;

	i = 0;
	if (word[i] == '~' && ft_strlen(word) == 1)
		return (ft_strdup(expand_env_value("HOME", ctx)));
	res = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			process_quotes(word, &i, &res, ctx);
		else if (word[i] == '$' && word[i + 1])
			process_dollar(word, &i, &res, ctx);
		else
			append_char(&res, word[i++]);
	}
	return (res);
}
