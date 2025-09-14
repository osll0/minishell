/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:40:23 by seokson           #+#    #+#             */
/*   Updated: 2025/06/29 02:46:15 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *nbr)
{
	long			sign;
	unsigned long	res;

	sign = 1;
	res = 0;
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign = -1;
		nbr++;
	}
	while (ft_isdigit(*nbr))
		res = res * 10 + *(nbr++) - '0';
	return ((long)(res * sign));
}
