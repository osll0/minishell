/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:36:11 by seokson           #+#    #+#             */
/*   Updated: 2025/04/18 22:36:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_base_len(unsigned long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

void	ft_padding_len(t_format info, long n, int *pad, int *zpad)
{
	int	len;

	if (n < 0)
		len = ft_base_len((unsigned long)(-n), 10);
	else
		len = ft_base_len((unsigned long)n, 10);
	*zpad = 0;
	if (info.precision > len)
		*zpad = info.precision - len;
	len = len + *zpad + (n < 0 || info.plus_flag || info.space_flag);
	*pad = 0;
	if (info.width > len)
		*pad = info.width - len;
}
