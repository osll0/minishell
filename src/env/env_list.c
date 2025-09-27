/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:16:11 by seokson           #+#    #+#             */
/*   Updated: 2025/09/20 16:08:06 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

const char	*env_get(t_env *head, const char *key)
{
	t_env	*cur;

	cur = head;
	while (cur)
	{
		if (cur->key && key && ft_strcmp(cur->key, key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

static int	update_existing_value(t_env *node, const char *val)
{
	char	*new_val;

	if (val == NULL)
	{
		free(node->value);
		node->value = NULL;
		return (0);
	}
	new_val = ft_strdup(val);
	if (new_val == NULL)
		return (-1);
	free(node->value);
	node->value = new_val;
	return (0);
}

int	env_set(t_env **head, const char *key, const char *val)
{
	t_env	*cur;

	if (!head || !key)
		return (-1);
	cur = *head;
	while (cur)
	{
		if (cur->key && ft_strcmp(cur->key, key) == 0)
			return (update_existing_value(cur, val));
		cur = cur->next;
	}
	cur = env_new(key, val);
	if (!cur)
		return (-1);
	env_push_back(head, cur);
	return (0);
}

int	env_unset(t_env **head, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!head || !*head || !key)
		return (1);
	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->key && ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

void	env_free(t_env **head)
{
	t_env	*cur;
	t_env	*next;

	if (head == NULL)
		return ;
	cur = *head;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*head = NULL;
}
