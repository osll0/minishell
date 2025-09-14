/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:53:59 by seokson           #+#    #+#             */
/*   Updated: 2025/07/08 13:23:13 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(const char **s)
{
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
		{
			(*s)++;
			return (-1);
		}
	}
	return (1);
}

static double	parse_integer(const char **s)
{
	double	res;

	res = 0.0;
	while (ft_isdigit(**s))
		res = res * 10 + (*(*s)++ - '0');
	return (res);
}

static double	parse_fraction(const char **s)
{
	double	res;
	double	div;

	res = 0.0;
	div = 1.0;
	if (**s == '.')
	{
		(*s)++;
		while (ft_isdigit(**s))
		{
			div *= 10;
			res += (*(*s)++ - '0') / div;
		}
	}
	return (res);
}

double	ft_atod(const char *nbr)
{
	int		sign;
	double	int_part;
	double	frac_part;

	if (!nbr)
		return (0);
	sign = parse_sign(&nbr);
	int_part = parse_integer(&nbr);
	frac_part = parse_fraction(&nbr);
	return (sign * (int_part + frac_part));
}
