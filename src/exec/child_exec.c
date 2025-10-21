/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:39:56 by seokson           #+#    #+#             */
/*   Updated: 2025/10/18 17:42:54 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "parser.h"
#include "builtin.h"
#include "minishell_signal.h"

static void	child_cleanup_and_exit(const t_ast *ast, t_env *env, int rc)
{
	if (ast)
		free_ast((t_ast *)ast);
	if (env)
		env_free(&env);
	exit(rc);
}

void	child_exec(const t_cmd *cmd, t_env *env, const t_ast *ast)
{
	int			rc;
	t_builtin	bk;

	set_signals_child();
	if (apply_redirs(cmd->redirs, cmd->n_redirs) < 0)
		child_cleanup_and_exit(ast, env, 1);
	if (cmd->argc == 0 || !cmd->argv || !cmd->argv[0])
		child_cleanup_and_exit(ast, env, 0);
	bk = builtin_lookup(cmd->argv[0]);
	if (bk != BUILTIN_NONE)
	{
		rc = builtin_exec_child(bk, cmd->argv, env);
		child_cleanup_and_exit(ast, env, rc);
	}
	rc = resolve_and_exec(cmd->argv, env);
	child_cleanup_and_exit(ast, env, rc);
}
