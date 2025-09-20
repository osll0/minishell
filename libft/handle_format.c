/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:02:28 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 20:03:03 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(const char **fmt, va_list args)
{
	t_format	info;

	info = parse_format(fmt);
	if (info.type == 'c')
		return (handle_char(info, va_arg(args, int)));
	else if (info.type == 's')
		return (handle_string(info, va_arg(args, char *)));
	else if (info.type == 'p')
		return (handle_pointer(info, va_arg(args, void *)));
	else if (info.type == 'd' || info.type == 'i')
		return (handle_int(info, va_arg(args, int)));
	else if (info.type == 'u')
		return (handle_unsigned(info, va_arg(args, unsigned int)));
	else if (info.type == 'x' || info.type == 'X')
		return (handle_hex(info, va_arg(args, unsigned int), info.type == 'X'));
	else if (info.type == '%')
		return (handle_char(info, '%'));
	return (0);
}
