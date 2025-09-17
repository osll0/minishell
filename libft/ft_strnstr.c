/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:47:24 by seokson           #+#    #+#             */
/*   Updated: 2025/04/05 11:41:55 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*hs;
	const char	*nd;
	size_t		cnt;

	if (!*little)
		return ((char *)big);
	cnt = 0;
	while (*big && len > 0)
	{
		hs = big;
		nd = little;
		cnt = len;
		while (*nd && *hs == *nd && cnt > 0)
		{
			hs++;
			nd++;
			cnt--;
		}
		if (*nd == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
