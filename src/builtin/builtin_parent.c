/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:00:17 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 15:18:35 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "builtin.h"

static int	builtin_cd(char **argv, t_env **env)
{
	(void)argv;
	(void)env;
	fprintf(stderr,"minishell: cd: not implemented\n");
	return (1);
}

static int	builtin_export(char **argv, t_env **env)
{
	(void)argv;
	(void)env;
	fprintf(stderr,"minishell: export: not implemented\n");
	return (1);
}

static int	builtin_unset(char **argv, t_env **env)
{
	(void)argv;
	(void)env;
	fprintf(stderr,"minishell: unset: not implemented\n");
	return (1);
}

static int	builtin_exit(char **argv, int last_status)
{
	(void)argv;
	(void)last_status;
	fprintf(stderr,"minishell: exit: not implemented\n");
	return (1);
}

int	builtin_exec_parent(t_builtin k, char **argv, t_env *env)
{
	t_env *temp;

	temp = env;
	if (k == BUILTIN_CD)
		return (builtin_cd(argv, &temp));
	if (k == BUILTIN_EXPORT)
		return (builtin_export(argv, &temp));
	if (k == BUILTIN_UNSET)
		return (builtin_unset(argv, &temp));
	if (k == BUILTIN_EXIT)
		return (builtin_exit(argv, 0));
	return (0);
}
