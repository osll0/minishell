/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:34:19 by seokson           #+#    #+#             */
/*   Updated: 2025/10/09 17:51:10 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "env.h"
#include "exec.h"

static int	handle_slash_exec(char **argv, char **envp)
{
	int	rc;

	execve(argv[0], argv, envp);
	if (errno == ENOEXEC)
		return (exec_with_sh(argv, envp, argv[0]));
	rc = ex_errno_code(errno);
	ex_report_exec(argv[0], errno, 1);
	return (rc);
}

static int	handle_path_exec(char **argv, t_env *env, char **envp)
{
	int			rc;
	int			last_err;
	const char	*path;

	rc = 1;
	last_err = ENOENT;
	path = env_get(env, "PATH");
	rc = search_path_exec(argv, path, envp, &last_err);
	if (rc != 0)
		ex_report_exec(argv[0], last_err, 0);
	return (rc);
}

int	resolve_and_exec(char **argv, t_env *env)
{
	int		rc;
	char	**envp;

	rc = 1;
	envp = env_to_array(env);
	if (!envp)
		return (1);
	if (ft_strchr(argv[0], '/'))
		rc = handle_slash_exec(argv, envp);
	else
		rc = handle_path_exec(argv, env, envp);
	free_env_array(envp);
	return (rc);
}
