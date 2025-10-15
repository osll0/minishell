/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:45:36 by seokson           #+#    #+#             */
/*   Updated: 2025/10/05 18:21:08 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "builtin.h"

int	bi_is_single_dash(const char *s)
{
	if (s == NULL)
		return (0);
	return (s[0] == '-' && s[1] == '\0');
}

int	bi_is_double_dash(const char *s)
{
	if (s == NULL)
		return (0);
	return (s[0] == '-' && s[1] == '-' && s[2] == '\0');
}

int	bi_is_triple_dash(const char *s)
{
	if (s == NULL)
		return (0);
	return (s[0] == '-' && s[1] == '-' && s[2] == '-' && s[3] == '\0');
}

int	bi_is_option_token(const char *s)
{
	if (s == NULL)
		return (0);
	if (s[0] != '-')
		return (0);
	if (s[1] == '\0')
		return (0);
	if (s[1] == '-' && s[2] == '\0')
		return (0);
	return (1);
}
