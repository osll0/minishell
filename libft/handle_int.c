/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:15:11 by seokson           #+#    #+#             */
/*   Updated: 2025/04/17 21:18:48 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_sign(t_format info, long n)
{
	if (n < 0)
		return (write(1, "-", 1));
	if (info.plus_flag)
		return (write(1, "+", 1));
	if (info.space_flag)
		return (write(1, " ", 1));
	return (0);
}

int	handle_int(t_format info, int n)
{
	int		cnt;
	int		padding;
	int		zero_padding;
	long	nb;

	cnt = 0;
	nb = (long)n;
	ft_padding_len(info, nb, &padding, &zero_padding);
	if (!info.minus_flag && (!info.zero_flag || info.dot_flag))
		cnt += ft_put_padding(' ', padding);
	cnt += put_sign(info, nb);
	if (!info.minus_flag && info.zero_flag && !info.dot_flag)
		cnt += ft_put_padding('0', padding);
	cnt += ft_put_padding('0', zero_padding);
	if (!(info.dot_flag && info.precision == 0 && nb == 0))
		cnt += ft_put_absnbr(nb);
	if (info.minus_flag)
		cnt += ft_put_padding(' ', padding);
	return (cnt);
}
