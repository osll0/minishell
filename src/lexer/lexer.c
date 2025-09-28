/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:53:50 by seunbaek          #+#    #+#             */
/*   Updated: 2025/09/27 16:53:15 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*new_token(const char *val, t_token_type type)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = ft_strdup(val);
	t->type = type;
	t->next = (NULL);
	return (t);
}

static size_t	add_token(t_token **head, t_token *newt, size_t	i)
{
	t_token	*tmp;

	if (!*head)
		*head = newt;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newt;
	}
	return (i);
}

static size_t	parse_word(const char *line, size_t *i, t_token **head)
{
	char	*word;
	char	quote;
	size_t	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
		break ;
}

t_token	*tokenize_input(const char *line)
{
	t_token	*tokens;
	size_t	i;

	tokens = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			i += add_token(&tokens, new_token("|", TOKEN_PIPE), 1);
		else if (line[i] == '<' && line[i + 1] == '<')
			i += add_token(&tokens, new_token("<<", TOKEN_HEREDOC), 2);
		else if (line[i] == '>' && line[i + 1] == '>')
			i += add_token(&tokens, new_token(">>", TOKEN_REDIR_APPEND), 2);
		else if (line[i] == '<')
			i += add_token(&tokens, new_token('<', TOKEN_REDIR_IN), 1);
		else if (line[i] == '>')
			i += add_token(&tokens, new_token('>', TOKEN_REDIR_OUT), 1);
		else
			if (parse_word(line, &i, &tokens) == 0)
				return (0);
	}
	return (tokens);
}
