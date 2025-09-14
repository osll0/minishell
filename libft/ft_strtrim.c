/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:42:24 by seokson           #+#    #+#             */
/*   Updated: 2025/04/12 15:51:38 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*start;
	const char	*end;
	char		*temp;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_isinset(*start, set))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && ft_isinset(*(end - 1), set))
		end--;
	len = end - start;
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_memcpy(temp, start, len);
	temp[len] = '\0';
	return (temp);
}
