/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:55:48 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 19:56:25 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	init_format(void)
{
	t_format	info;

	info.minus_flag = 0;
	info.zero_flag = 0;
	info.dot_flag = 0;
	info.hash_flag = 0;
	info.space_flag = 0;
	info.plus_flag = 0;
	info.width = 0;
	info.precision = 0;
	info.type = '\0';
	return (info);
}
