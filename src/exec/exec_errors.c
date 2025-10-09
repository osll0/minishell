/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:30:12 by seokson           #+#    #+#             */
/*   Updated: 2025/10/07 14:26:07 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "exec.h"

int	ex_errno_code(int err)
{
	if (err == ENOENT || err == ENOTDIR)
		return (127);
	if (err == EACCES || err == EISDIR || err == ENOEXEC || err == ELOOP)
		return (126);
	return (1);
}

void	ex_print_err(const char *name, const char *msg)
{
	write(2, "minishell: ", 11);
	if (name)
	{
		write(2, name, (int)ft_strlen(name));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, (int)ft_strlen(msg));
	write(2, "\n", 1);
}

void	ex_report_exec(const char *name, int err, int has_slash)
{
	const char	*m;

	if (!has_slash)
	{
		if (err == ENOENT || err == ENOTDIR)
			return (ex_print_err(name, "command not found"));
		if (err == EACCES)
			return (ex_print_err(name, "Permission denied"));
		if (err == EISDIR)
			return (ex_print_err(name, "Is a directory"));
		if (err == ELOOP)
			return (ex_print_err(name, "Too many levels of symbolic links"));
		if (err == ENOEXEC)
			return (ex_print_err(name, "Exec format error"));
		return (ex_print_err(name, "command not found"));
	}
	else
	{
		m = strerror(err);
		if (!m)
			m = "error";
		ex_print_err(name, m);
	}
}
