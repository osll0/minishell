/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:54:09 by seokson           #+#    #+#             */
/*   Updated: 2025/04/12 15:39:37 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_copy;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	len_copy = len_s - start;
	if (len_copy > len)
		len_copy = len;
	str = (char *)malloc(len_copy + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_copy)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
