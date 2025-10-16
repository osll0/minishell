/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:27:12 by seokson           #+#    #+#             */
/*   Updated: 2025/10/16 18:57:05 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "exec.h"
#include "env.h"

int	execute_ast(const t_ast *ast, t_env **penv)
{
	int	rc;
	int	exit_code;

	if (!ast)
		return (0);
	if (ast->type == N_CMD)
		rc = execute_single_cmd(&ast->cmd, penv);
	else
		rc = execute_pipe(ast, penv);
	if (rc >= 256)
	{
		exit_code = (unsigned char)(rc - 256);
		env_free(penv);
		rl_clear_history();
		exit(exit_code);
	}
	return (rc);
}
