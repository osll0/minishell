/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:59:13 by seokson           #+#    #+#             */
/*   Updated: 2025/04/05 11:04:12 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*dst;

	tmp = (char *)malloc(ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	dst = tmp;
	while (*s)
		*tmp++ = *s++;
	*tmp = '\0';
	return (dst);
}
