/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:45:11 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 22:45:51 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_format info, int c)
{
	int	count;
	int	padding;

	count = 0;
	padding = 0;
	if (info.width > 1)
		padding = info.width - 1;
	if (!info.minus_flag)
		count += ft_put_padding(' ', padding);
	count += write(1, &c, 1);
	if (info.minus_flag)
		count += ft_put_padding(' ', padding);
	return (count);
}
