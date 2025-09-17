/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:32:20 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 17:36:40 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static int	is_echo_nopt(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	builtin_echo(char **argv)
{
	int	i;
	int	no_nl;
	int	first;

	i = 1;
	no_nl = 0;
	while (argv[i] && is_echo_nopt(argv[i]))
	{
		no_nl = 1;
		i++;
	}
	first = 1;
	while (argv[i])
	{
		if (!first)
			write(1, " ", 1);
		write(1, argv[i], (int)ft_strlen(argv[i]));
		first = 0;
		i++;
	}
	if (!no_nl)
		write(1, "\n", 1);
	return (0);
}
