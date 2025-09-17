/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:01:43 by seokson           #+#    #+#             */
/*   Updated: 2025/04/20 17:22:23 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_pointer(t_format info, void *ptr)
{
	unsigned long	addr;
	int				count;
	int				len;
	int				padding;

	count = 0;
	if (!ptr)
		return (handle_string(info, "(nil)"));
	addr = (unsigned long)ptr;
	len = ft_base_len(addr, 16);
	if (info.dot_flag && info.precision == 0 && addr == 0)
		len = 0;
	padding = 0;
	if (info.width > 2 + len)
		padding = info.width - (2 + len);
	if (!info.minus_flag)
		count += ft_put_padding(' ', padding);
	count += ft_put_prefix(0);
	if (!(info.dot_flag && info.precision == 0 && addr == 0))
		count += ft_put_hex(addr, 0);
	if (info.minus_flag)
		count += ft_put_padding(' ', padding);
	return (count);
}
