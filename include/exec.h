/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:50:40 by seokson           #+#    #+#             */
/*   Updated: 2025/10/07 14:22:39 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
# include "env.h"
# include "pipe.h"

int		execute_ast(const t_ast *ast, t_env **penv);
int		execute_single_cmd(const t_cmd *cmd, t_env **penv);
int		execute_pipe(const t_ast *node, t_env **penv);

void	child_exec(const t_cmd *cmd, t_env *env);

int		apply_redirs(t_redir *redirs, int n_redirs);

int		spawn_stage(const t_cmd *cmd, t_pipe *p, int need_pipe);

char	**split_path(const char *s);

int		search_path_exec(char **argv, const char *path, char **envp, int *perr);

int		resolve_and_exec(char **argv, t_env *env);

int		run_builtin_parent_with_redirs(const t_cmd *cmd, t_env **penv);

int		exec_with_sh(char **argv, char **envp, const char *file);
int		ex_path_err_reduce(int acc, int now_err);
int		ex_path_err_finalize(int acc, int last_err);

/* exec error helpers */
int		ex_errno_code(int err);
void	ex_print_err(const char *name, const char *msg);
void	ex_report_exec(const char *name, int err, int has_slash);

#endif
