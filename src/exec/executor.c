/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:27:12 by seokson           #+#    #+#             */
/*   Updated: 2025/10/05 12:55:14 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

int	execute_ast(const t_ast *ast, t_env **penv)
{
	if (!ast)
		return (0);
	if (ast->type == N_CMD)
		return (execute_single_cmd(&ast->cmd, penv));
	return (execute_pipe(ast, penv));
}
