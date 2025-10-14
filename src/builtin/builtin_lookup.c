/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:02:53 by seokson           #+#    #+#             */
/*   Updated: 2025/09/15 18:30:58 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

t_builtin	builtin_lookup(const char *name)
{
	if (!name)
		return (BUILTIN_NONE);
	if (ft_strcmp(name, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(name, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(name, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(name, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(name, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(name, "unset") == 0)
		return (BUILTIN_UNSET);
	if (ft_strcmp(name, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}
