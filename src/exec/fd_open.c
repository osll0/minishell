/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:42:54 by seokson           #+#    #+#             */
/*   Updated: 2025/08/29 12:55:44 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	x_open_ro(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	while (fd < 0 && errno == EINTR)
		fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("minishell: open (Read_Only");
	return (fd);
}

int	x_open_trunc(const char *path, mode_t mode)
{
	int	fd;

	fd = open(path, O_RDONLY);
	while (fd < 0 && errno == EINTR)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
		perror("minishell: open (Trunc)");
	return (fd);
}

int	x_open_append(const char *path, mode_t mode)
{
	int	fd;

	fd = open(path, O_RDONLY);
	while (fd < 0 && errno == EINTR)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, mode);
	if (fd < 0)
		perror("minishell: open (Append)");
	return (fd);
}
