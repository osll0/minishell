/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:37:25 by seokson           #+#    #+#             */
/*   Updated: 2025/04/18 16:40:47 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_hpadding_len(t_format info, unsigned int n, int *pad, int *zpad)
{
	int	len;

	len = ft_base_len(n, 16);
	*zpad = 0;
	if (info.precision > len)
		*zpad = info.precision - len;
	if (info.hash_flag && n != 0)
		len += 2;
	len += *zpad;
	*pad = 0;
	if (info.width > len)
		*pad = info.width - len;
}

int	handle_hex(t_format info, unsigned int n, int uppercase)
{
	int	count;
	int	padding;
	int	zero_padding;

	count = 0;
	get_hpadding_len(info, n, &padding, &zero_padding);
	if (!info.minus_flag && (!info.zero_flag || info.dot_flag))
		count += ft_put_padding(' ', padding);
	if (info.hash_flag && n != 0)
		count += ft_put_prefix(uppercase);
	if (!info.minus_flag && info.zero_flag && !info.dot_flag)
		count += ft_put_padding('0', padding);
	count += ft_put_padding('0', zero_padding);
	if (!(info.dot_flag && info.precision == 0 && n == 0))
		count += ft_put_hex(n, uppercase);
	if (info.minus_flag)
		count += ft_put_padding(' ', padding);
	return (count);
}
