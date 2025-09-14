/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:43:37 by seokson           #+#    #+#             */
/*   Updated: 2025/04/15 19:43:48 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(const char **format, t_format *info)
{
	while (**format == '-' || **format == '0' || **format == '+'
		|| **format == ' ' || **format == '#')
	{
		if (**format == '-')
			info->minus_flag = 1;
		else if (**format == '0')
			info->zero_flag = 1;
		else if (**format == '#')
			info->hash_flag = 1;
		else if (**format == ' ')
			info->space_flag = 1;
		else if (**format == '+')
			info->plus_flag = 1;
		(*format)++;
	}
}

static void	parse_width(const char **format, t_format *info)
{
	while (**format >= '0' && **format <= '9')
	{
		info->width = info->width * 10 + (**format - '0');
		(*format)++;
	}
}

static void	parse_precision(const char **format, t_format *info)
{
	if (**format == '.')
	{
		info->dot_flag = 1;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			info->precision = info->precision * 10 + (**format - '0');
			(*format)++;
		}
	}
}

static void	parse_type(const char **format, t_format *info)
{
	if (**format == 'c' || **format == 's' || **format == 'p'
		|| **format == 'd' || **format == 'i' || **format == 'u'
		|| **format == 'x' || **format == 'X' || **format == '%')
	{
		info->type = **format;
		(*format)++;
	}
	else if (**format)
		(*format)++;
}

t_format	parse_format(const char **format)
{
	t_format	info;

	info = init_format();
	parse_flags(format, &info);
	parse_width(format, &info);
	parse_precision(format, &info);
	parse_type(format, &info);
	normalize_flags(&info);
	return (info);
}
