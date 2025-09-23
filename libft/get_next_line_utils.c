/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shson <shson@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:23:48 by seokson           #+#    #+#             */
/*   Updated: 2025/04/25 18:02:52 by shson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(const char *s1, const char *s2)
{
	char	*temp;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (gnl_strjoin("", s2));
	else if (!s2)
		return (gnl_strjoin(s1, ""));
	temp = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!temp)
		return (NULL);
	ptr = temp;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (temp);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_copy;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	len_s = gnl_strlen(s);
	if (start >= len_s)
		return (gnl_strjoin("", ""));
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
