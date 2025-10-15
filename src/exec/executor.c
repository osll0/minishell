/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:27:12 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 15:56:01 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

int	execute_ast(const t_ast *ast, t_env *env)
{
	if (!ast)
		return (0);
	if (ast->type == N_CMD)
		return (execute_single_cmd(&ast->cmd, env));
	return (execute_pipe(ast, env));
}
