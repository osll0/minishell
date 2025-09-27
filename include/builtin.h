/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:05:01 by seokson           #+#    #+#             */
/*   Updated: 2025/09/27 16:25:14 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"

typedef enum e_builtin
{
	BUILTIN_NONE = 0,
	BUILTIN_ECHO,
	BUILTIN_PWD,
	BUILTIN_ENV,
	BUILTIN_CD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_EXIT
}	t_builtin;

t_builtin	builtin_lookup(const char *name);
int			builtin_exec_child(t_builtin kind, char **argv, t_env *env);
int			builtin_exec_parent(t_builtin kind, char **argv, t_env **penv);

int			builtin_echo(char **argv);
int			builtin_pwd(char **argv);
int			builtin_env(char **argv, t_env *env);

int			builtin_cd(char *const *argv, t_env **penv);
int			builtin_export(char *const *argv, t_env **penv);
int			builtin_unset(char *const *argv, t_env **penv);
int			builtin_exit(char *const *argv, int *do_exit, int *exit_status);

int			bi_is_single_dash(const char *s);
int			bi_is_double_dash(const char *s);
int			bi_is_triple_dash(const char *s);
int			bi_is_option_token(const char *s);

void		bi_strtab_sort(char **tab);
void		bi_print_err(const char *p, const char *msg, const char *arg);
int			bi_is_valid_identifier(const char *s);
int			bi_parse_longlong(const char *s, long long *out, int *overflow);
#endif
