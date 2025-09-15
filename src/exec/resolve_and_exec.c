/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:24:59 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 16:52:05 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "exec.h"
#include "env.h"
#include "libft.h"

static int	map_errno_to_status(int err)
{
	if (errno == ENOENT)
		return (127);
	if (errno == EACCES || errno == EISDIR)
		return (126);
	return (1);
}

static int	try_exec_direct(char **argv, char **envp)
{
	execve(argv[0], argv, envp);
	return (map_errno_to_status(errno));
}

static char	*join_dir_cmd(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static int	search_path_and_exec(char **argv, const char *path, char **envp)
{
	char	**dirs;
	char	*full;
	int		i;
	int		last_err;

	if (!path || *path == '\0')
		return (127);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (1);
	i = 0;
	last_rer = ENOENT;
	while (dirs[i])
	{
		full = join_dir_cmd(dirs[i], argv[0]);
		if (!full)
			break ;
		execve(full, argv, envp);
		last_err = errno;
		free(full);
		i++;
	}
	ft_split_free(dirs);
	return (map_errno_to_status(last_err));
}

int	resolve_and_exec(char **argv, t_env *env)
{
	int		rc;
	char	*path;
	char	**envp;

	envp = env_to_array(env);
	if (!envp)
		return (1);
	if (ft_strchr(argv[0], '/'))
	{
		rc = try_exec_direct(argv, envp);
		free_envp_array(envp);
		return (rc);
	}
	path = split_path_and_exec(argv, path, envp);
	rc = search_path_and_exec(argv, path, envp);
	free_env_array(envp);
	return (rc);
}
