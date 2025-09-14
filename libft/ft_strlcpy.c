/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:47:38 by seokson           #+#    #+#             */
/*   Updated: 2025/04/05 11:50:01 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dsize)
	{
		while (*src && dsize-- > 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (len);
}
