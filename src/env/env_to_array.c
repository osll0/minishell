/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:06:52 by seokson           #+#    #+#             */
/*   Updated: 2025/09/20 15:09:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

static size_t	env_len(t_env *head)
{
	size_t	n;
	t_env	*cur;

	n = 0;
	cur = head;
	while (cur != NULL)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

static char	*make_env_entry(const char *k, const char *v)
{
	size_t	len_k;
	size_t	len_v;
	char	*s;

	len_k = 0;
	len_v = 0;
	if (k != NULL)
		len_k = ft_strlen(k);
	if (v != NULL)
		len_v = ft_strlen(v);
	s = (char *)malloc(len_k + 1 + len_v + 1);
	if (s == NULL)
		return (NULL);
	if (len_k > 0)
		ft_memcpy(s, k, len_k);
	s[len_k] = '=';
	if (len_v > 0)
		ft_memcpy(s + len_k + 1, v, len_v);
	s[len_k + 1 + len_v] = '\0';
	return (s);
}

static int	fill_array(char **arr, t_env *head)
{
	size_t	i;
	t_env	*cur;
	char	*entry;

	i = 0;
	cur = head;
	while (cur != NULL)
	{
		entry = make_env_entry(cur->key, cur->value);
		if (entry == NULL)
			return (-1);
		arr[i] = entry;
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (0);
}

void	free_env_array(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**env_to_array(t_env *head)
{
	size_t	n;
	char	**arr;
	int		rc;

	n = env_len(head);
	arr = (char **)ft_calloc(n + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	rc = fill_array(arr, head);
	if (rc == -1)
	{
		free_env_array(arr);
		return (NULL);
	}
	return (arr);
}
