/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:58:03 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 19:58:11 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	normalize_flags(t_format *info)
{
	if (info->minus_flag)
		info->zero_flag = 0;
	if (info->plus_flag)
		info->space_flag = 0;
	if (info->dot_flag
		&& (info->type == 'd' || info->type == 'i'
			|| info->type == 'u' || info->type == 'x'
			|| info->type == 'X'))
		info->zero_flag = 0;
}
