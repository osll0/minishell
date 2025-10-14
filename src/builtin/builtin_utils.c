/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:06:11 by seokson           #+#    #+#             */
/*   Updated: 2025/09/27 16:16:33 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

void	bi_strtab_sort(char **tab)
{
	int		i;
	int		j;
	char	*key;

	if (tab == NULL)
		return ;
	i = 1;
	while (tab[i] != NULL)
	{
		key = tab[i];
		j = i;
		while (j > 0 && ft_strcmp(tab[j - 1], key) > 0)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = key;
		i++;
	}
}

void	bi_print_err(const char *p, const char *msg, const char *arg)
{
	write(2, "minishell: ", 11);
	if (p != NULL)
	{
		write(2, p, (size_t)ft_strlen(p));
	}
	if (msg != NULL)
	{
		write(2, ": ", 2);
		write(2, msg, (size_t)ft_strlen(msg));
	}
	if (arg != NULL)
	{
		write(2, ": ", 2);
		write(2, arg, (size_t)ft_strlen(arg));
	}
	write(2, "\n", 1);
}

int	bi_is_valid_identifier(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	if (s[0] == '\0')
		return (0);
	if (!(ft_isalpha((int)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] != '\0')
	{
		if (!(ft_isalnum((int)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_sign(const char *s, int *idx)
{
	int	sign;

	sign = 1;
	if (s[*idx] == '+' || s[*idx] == '-')
	{
		if (s[*idx] == '-')
			sign = -1;
		(*idx)++;
	}
	return (sign);
}

int	bi_parse_longlong(const char *s, long long *out, int *overflow)
{
	int			i;
	int			sign;
	long long	acc;

	if (s == NULL || *s == '\0')
		return (0);
	*out = 0;
	*overflow = 0;
	i = 0;
	sign = parse_sign(s, &i);
	if (s[i] == '\0')
		return (0);
	acc = 0;
	while (s[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		if (acc > (9223372036854775807LL - (s[i] - '0')) / 10)
			*overflow = 1;
		acc = acc * 10 + (s[i] - '0');
		i++;
	}
	*out = acc * sign;
	return (1);
}
