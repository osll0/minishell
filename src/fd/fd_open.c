/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:42:54 by seokson           #+#    #+#             */
/*   Updated: 2025/10/06 16:20:55 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "fd_utils.h"

int	x_open_ro(const char *path)
{
	int	fd;

	while (1)
	{
		fd = open(path, O_RDONLY);
		if (fd >= 0)
			return (fd);
		if (errno == EINTR)
			continue ;
		return (-1);
	}
}

int	x_open_trunc(const char *path, mode_t mode)
{
	int	fd;

	while (1)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
		if (fd >= 0)
			return (fd);
		if (errno == EINTR)
			continue ;
		return (-1);
	}
}

int	x_open_append(const char *path, mode_t mode)
{
	int	fd;

	while (1)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, mode);
		if (fd >= 0)
			return (fd);
		if (errno == EINTR)
			continue ;
		return (-1);
	}
}
