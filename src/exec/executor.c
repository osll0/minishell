/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:27:12 by seokson           #+#    #+#             */
/*   Updated: 2025/10/17 01:28:52 by seokson          ###   ########.fr       */
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

	if (!ast)
		return (2);
	if (ast->type == N_CMD)
		rc = execute_single_cmd(&ast->cmd, penv);
	else
		rc = execute_pipe(ast, penv);
	return (rc);
}
