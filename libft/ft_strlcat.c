/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:13:19 by seokson           #+#    #+#             */
/*   Updated: 2025/04/02 14:20:52 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	char		*d;
	const char	*s;
	size_t		len_d;

	len_d = ft_strlen(dst);
	d = dst + len_d;
	s = src;
	if (dsize <= len_d)
		return (dsize + ft_strlen(src));
	dsize = dsize - len_d;
	while (*s && dsize-- > 1)
		*d++ = *s++;
	*d = '\0';
	return (len_d + ft_strlen(src));
}
