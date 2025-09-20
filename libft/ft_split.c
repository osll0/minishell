/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:26:05 by seokson           #+#    #+#             */
/*   Updated: 2025/04/09 12:15:49 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	countw(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char *)malloc(n + 1);
	if (!temp)
		return (NULL);
	while (i < n)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

int	split_loop(char	**res, const char *s, char c)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (s > start)
		{
			res[i] = ft_strndup(start, s - start);
			if (!res[i++])
			{
				free_all(res, i);
				return (1);
			}
		}
	}
	res[i] = NULL;
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**temp;

	if (!s)
		return (NULL);
	temp = (char **)malloc(sizeof(char *) * (countw(s, c) + 1));
	if (!temp)
		return (NULL);
	if (split_loop(temp, s, c))
		return (NULL);
	return (temp);
}
