/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:05:01 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 17:36:39 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ast.h"

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
int			builtin_exec_parent(t_builtin kind, char **argv, t_env *env);

int			builtin_echo(char **argv);
int			builtin_pwd(char **argv);
int			builtin_env(char **argv, t_env *env);

#endif
