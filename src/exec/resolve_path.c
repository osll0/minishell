/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:29:41 by seokson           #+#    #+#             */
/*   Updated: 2025/10/07 16:14:54 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "exec.h"
#include "env.h"
#include "libft.h"

/* dir가 ""면 "."로 치환, 디렉터리 검색권한(x) 없으면 *pskip=1 후 NULL 반환
   그 외에는 d + "/" + cmd 를 만들어 반환(*pskip=0)
   반환값이 NULL 이고 *pskip==0 이면 메모리 오류로 본다. */
static char	*join_dir_cmd_checked(const char *dir, const char *cmd, int *pskip)
{
	const char	*base;
	char		*temp;
	char		*full;

	base = ".";
	if (dir && dir[0] != '\0')
		base = dir;
	if (access(base, X_OK) == -1)
	{
		*pskip = 1;
		return (NULL);
	}
	*pskip = 0;
	temp = ft_strjoin(base, "/");
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

/* 반환: -1=메모리 등 내부에러 → 즉시 1 반환
         0=계속(다음 PATH 요소)
         1=ENOEXEC 처리 완료 → *plast_err에 최종 rc 저장, 즉시 return */
static int	exec_one_dir(char **argv, char **envp,
						const char *dir, int *plast_err)
{
	int		skip;
	char	*full;

	full = join_dir_cmd_checked(dir, argv[0], &skip);
	if (skip)
		return (0);
	if (!full)
		return (-1);
	execve(full, argv, envp);
	*plast_err = errno;
	if (*plast_err == ENOEXEC)
	{
		*plast_err = exec_with_sh(argv, envp, full);
		free(full);
		return (1);
	}
	free(full);
	return (0);
}

static int	try_exec_dirs(char **argv, char **dirs, char **envp, int *perr)
{
	int	r;
	int	i;
	int	acc;
	int	last_err;

	i = 0;
	acc = ENOENT;
	last_err = ENOENT;
	while (dirs[i])
	{
		r = exec_one_dir(argv, envp, dirs[i], &last_err);
		if (r == -1)
			return (1);
		if (r == 1)
			return (last_err);
		acc = ex_path_err_reduce(acc, last_err);
		i++;
	}
	if (perr)
		*perr = ex_path_err_finalize(acc, last_err);
	return (ex_errno_code(ex_path_err_finalize(acc, last_err)));
}

int	search_path_exec(char **argv, const char *path, char **envp, int *perr)
{
	int		rc;
	char	**dirs;

	rc = 127;
	dirs = NULL;
	if (!path || *path == '\0')
		return (127);
	dirs = split_path(path);
	if (!dirs)
		return (1);
	rc = try_exec_dirs(argv, dirs, envp, perr);
	ft_split_free(dirs);
	return (rc);
}
