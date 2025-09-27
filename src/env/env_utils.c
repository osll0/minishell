/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:05:11 by seokson           #+#    #+#             */
/*   Updated: 2025/09/20 16:05:50 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

t_env	*env_new(const char *k, const char *v)
{
	t_env	*new_node;
	char	*key;
	char	*value;

	new_node = (t_env *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	key = NULL;
	value = NULL;
	if (k)
	{
		key = ft_strdup(k);
		if (!key)
			return (free(new_node), NULL);
	}
	if (v)
	{
		value = ft_strdup(v);
		if (!value)
			return (free(key), free(new_node), NULL);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	env_push_back(t_env **head, t_env *node)
{
	t_env	*cur;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}
