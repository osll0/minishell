/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:48:46 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 22:50:15 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_padding(char c, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		write(1, &c, 1);
		i++;
	}
	return (count);
}

int	ft_put_absnbr(long n)
{
	char			c;
	int				count;
	unsigned long	un;

	if (n < 0)
		un = (unsigned long)(-n);
	else
		un = (unsigned long)n;
	count = 0;
	if (un >= 10)
		count += ft_put_absnbr(un / 10);
	c = '0' + (un % 10);
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_put_prefix(int uppercase)
{
	if (uppercase)
		return (write(1, "0X", 2));
	else
		return (write(1, "0x", 2));
	return (0);
}

int	ft_put_hex(unsigned long n, int is_upper)
{
	char	*base;
	int		count;

	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_put_hex(n / 16, is_upper);
	count += write(1, &base[n % 16], 1);
	return (count);
}
