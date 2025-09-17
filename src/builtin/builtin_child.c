/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:43:38 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 17:36:32 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "builtin.h"

int	builtin_exec_child(t_builtin k, char **argv, t_env *env)
{
	if (k == BUILTIN_ECHO)
		return (builtin_echo(argv));
	if (k == BUILTIN_PWD)
		return (builtin_pwd(argv));
	if (k == BUILTIN_ENV)
		return (builtin_env(argv, env));
	return (1);
}
