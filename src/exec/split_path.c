/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:12:21 by seokson           #+#    #+#             */
/*   Updated: 2025/10/05 15:17:20 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "exec.h"

static size_t	path_field_count(const char *s)
{
	size_t	i;
	size_t	n;

	if (!s)
		return (0);
	i = 0;
	n = 1;
	while (s[i])
	{
		if (s[i] == ':')
			n++;
		i++;
	}
	return (n);
}

static int	path_fill_fields(const char *s, char **out)
{
	size_t	i;
	size_t	start;
	size_t	idx;

	i = 0;
	start = 0;
	idx = 0;
	while (1)
	{
		if (s[i] == ':' || s[i] == '\0')
		{
			out[idx] = ft_substr(s, start, i - start);
			if (!out[idx])
				return (-1);
			idx++;
			if (s[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	return (0);
}

char	**split_path(const char *s)
{
	char	**out;
	size_t	n;

	if (!s)
		return (NULL);
	n = path_field_count(s);
	out = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!out)
		return (NULL);
	if (path_fill_fields(s, out) < 0)
	{
		ft_split_free(out);
		return (NULL);
	}
	return (out);
}
