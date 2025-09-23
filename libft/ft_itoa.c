/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:20:15 by seokson           #+#    #+#             */
/*   Updated: 2025/04/07 17:38:30 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_len(int n, int *sign)
{
	int	len;

	len = (n <= 0);
	if (n < 0)
		*sign = -1;
	else
		*sign = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*temp;
	int		len;
	int		sign;

	len = check_len(n, &sign);
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	temp[len--] = '\0';
	if (n == 0)
		temp[len--] = '0';
	while (n)
	{
		temp[len--] = sign * (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		temp[0] = '-';
	return (temp);
}
