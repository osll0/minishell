/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:52:05 by seokson           #+#    #+#             */
/*   Updated: 2025/04/20 22:53:10 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	handle_string(t_format info, char *s)
{
	int	len;
	int	count;
	int	padding;

	count = 0;
	if (!s)
		s = "(null)";
	len = pf_strlen(s);
	if (info.dot_flag && info.precision < len)
		len = info.precision;
	padding = 0;
	if (info.width > len)
		padding = info.width - len;
	if (!info.minus_flag)
		count += ft_put_padding(' ', padding);
	write(1, s, len);
	count += len;
	if (info.minus_flag)
		count += ft_put_padding(' ', padding);
	return (count);
}
