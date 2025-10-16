/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:00:21 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/16 17:00:23 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "env.h"
#include "libft.h"

static const char	*expand_env_value(const char *key, t_env *env)
{
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(0));
	return (env_get(env, key));
}

static void	append_char(char **res, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(*res, tmp);
	free(*res);
	*res = joined;
}

static void	process_dollar(const char *word, int *i, char **res, t_env *env)
{
	int		start;
	char	*key;
	const char	*val;
	char	*tmp;

	(*i)++;
	start = *i;
	if (word[*i] != '?')
		while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
			(*i)++;
	else
		(*i)++;
	key = ft_substr(word, start, *i - start);
	val = expand_env_value(key, env);
	free(key);
	tmp = ft_strjoin(*res, val);
	free(*res);
	*res = tmp;
}

static void	process_quotes(const char *word, int *i, char **res, t_env *env)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
	{
		if (quote == '"' && word[*i] == '$' && word[*i + 1])
			process_dollar(word, i, res, env);
		else
		append_char(res, word[(*i)++]);
	}
}

char	*expand_word(const char *word, t_env *env)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			process_quotes(word, &i, &res, env);
		else if (word[i] == '$' && word[i + 1])
			process_dollar(word, &i, &res, env);
		else
			append_char(&res, word[i++]);
	}
	return (res);
}