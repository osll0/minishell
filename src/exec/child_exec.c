/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:39:56 by seokson           #+#    #+#             */
/*   Updated: 2025/10/06 15:18:18 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "exec.h"
#include "builtin.h"
#include "env.h"

void	child_exec(const t_cmd *cmd, t_env *env)
{
	int			rc;
	t_builtin	bk;

	if (apply_redirs(cmd->redirs, cmd->n_redirs) < 0)
		exit(1);
	if (cmd->argc == 0 || !cmd->argv || !cmd->argv[0])
		exit(0);
	bk = builtin_lookup(cmd->argv[0]);
	if (bk != BUILTIN_NONE)
	{
		rc = builtin_exec_child(bk, cmd->argv, env);
		exit(rc);
	}
	rc = resolve_and_exec(cmd->argv, env);
	exit(rc);
}
