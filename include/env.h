/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:20:20 by seokson           #+#    #+#             */
/*   Updated: 2025/09/21 12:04:36 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env		*env_new(const char *k, const char *v);
void		env_push_back(t_env **head, t_env *node);

const char	*env_get(t_env *head, const char *key);
int			env_set(t_env **head, const char *key, const char *val);
int			env_unset(t_env **head, const char *key);
void		env_free(t_env **head);

t_env		*env_from_environ(char *const *environ);
char		**env_to_array(t_env *head);
void		free_env_array(char **arr);

#endif
