/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:31:54 by seokson           #+#    #+#             */
/*   Updated: 2025/04/18 16:35:48 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_unsigned(t_format info, unsigned int n)
{
	int	count;
	int	padding;
	int	zero_padding;

	count = 0;
	ft_padding_len(info, n, &padding, &zero_padding);
	if (!info.minus_flag && (!info.zero_flag || info.dot_flag))
		count += ft_put_padding(' ', padding);
	if (!info.minus_flag && info.zero_flag && !info.dot_flag)
		count += ft_put_padding('0', padding);
	count += ft_put_padding('0', zero_padding);
	if (!(info.dot_flag && info.precision == 0 && n == 0))
		count += ft_put_absnbr((long)n);
	if (info.minus_flag)
		count += ft_put_padding(' ', padding);
	return (count);
}
