/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:07:58 by seokson           #+#    #+#             */
/*   Updated: 2025/09/14 16:52:04 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ast.h"
#include "fd_utils.h"

static int	apply_in(const char *path)
{
	int	fd;

	fd = x_open_ro(path);
	if (fd < 0)
		return (-1);
	if (x_dup2(fd, STDIN_FILENO) < 0)
	{
		x_close(fd);
		return (-1);
	}
	if (x_close(fd) < 0)
		return (-1);
	return (0);
}

static int	apply_out_trunc(const char *path)
{
	int	fd;

	fd = x_open_trunc(path, 0644);
	if (fd < 0)
		return (-1);
	if (x_dup2(fd, STDOUT_FILENO) < 0)
	{
		x_close(fd);
		return (-1);
	}
	if (x_close(fd) < 0)
		return (-1);
	return (0);
}

static int	apply_out_append(const char *path)
{
	int	fd;

	fd = x_open_append(path, 0644);
	if (fd < 0)
		return (-1);
	if (x_dup2(fd, STDOUT_FILENO) < 0)
	{
		x_close(fd);
		return (-1);
	}
	if (x_close(fd) < 0)
		return (-1);
	return (0);
}

static int	apply_here(t_redir *r)
{
	if (r->here_fd < 0)
		return (-1);
	if (x_dup2(r->here_fd, STDIN_FILENO) < 0)
	{
		x_close(r->here_fd);
		r->here_fd = -1;
		return (-1);
	}
	if (x_close(r->here_fd) < 0)
		return (-1);
	r->here_fd = -1;
	return (0);
}

/* R_IN / R_OUT / R_APP / R_HERE  enum으로 관리 */
int apply_redirs(t_redir *redirs, int n_redirs)
{
	int	i;

	i = 0;
	while (i < n_redirs)
	{
		if (redirs[i].ambig)
			return (-1);
		if (redirs[i].kind == R_IN
			&& apply_in(redirs[i].target) < 0)
			return (-1);
		else if (redirs[i].kind == R_OUT
			&& apply_out_append(redirs[i].target) < 0)
			return (-1);
		else if (redirs[i].kind == R_APP
			&& apply_out_append(redirs[i].target) < 0)
			return (-1);
		else if (redirs[i].kind == R_HERE
			&& apply_here(&redirs[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}
