/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_environ.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:58:51 by seokson           #+#    #+#             */
/*   Updated: 2025/09/20 16:10:27 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

static int	process_entry(t_env **head, const char *entry)
{
	const char	*eq;
	size_t		len;
	char		*key;
	char		*value;

	eq = ft_strchr(entry, '=');
	if (eq == NULL)
		return (0);
	len = (size_t)(eq - entry);
	key = ft_strndup(entry, len);
	if (key == NULL)
		return (-1);
	value = ft_strdup(eq + 1);
	if (value == NULL && *(eq + 1) != '\0')
		return (free(key), -1);
	if (env_set(head, key, value) == -1)
		return (free(key), free(value), -1);
	free(key);
	free(value);
	return (0);
}

t_env	*env_from_environ(char *const *environ)
{
	t_env	*head;
	int		i;
	int		rc;

	head = NULL;
	i = 0;
	while (environ != NULL && environ[i] != NULL)
	{
		rc = process_entry(&head, environ[i]);
		if (rc == -1)
		{
			env_free(&head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
