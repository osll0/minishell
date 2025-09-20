/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:50:40 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 14:33:48 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"

typedef struct s_pipe t_pipe;

int		execute_ast(const t_ast *ast, t_env *env);
int		execute_single_cmd(const t_cmd *cmd, t_env *env);
int		execute_pipe(const t_ast *node, t_env *env);

void	child_exec(const t_cmd *cmd, t_env *env);

int		apply_redirs(t_redir *redirs, int n_redirs);

int		spawn_stage(const t_cmd *cmd, t_pipe *p, int need_pipe);

int		resolve_and_exec(char **argv, t_env *env);

int		run_builtin_parent_with_redirs(const t_cmd *cmd, t_env *env);

#endif
