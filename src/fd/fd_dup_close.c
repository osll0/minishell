/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_dup_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:24:26 by seokson           #+#    #+#             */
/*   Updated: 2025/08/31 12:31:56 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "fd_utils.h"

static int	retry_close(int fd)
{
	while (1)
	{
		if (close(fd) == 0)
			return (0);
		if (errno == EINTR)
			continue ;
		return (-1);
	}
}

int	x_dup2(int oldfd, int newfd)
{
	int	r;

	r = dup2(oldfd, newfd);
	while (r < 0 && errno == EINTR)
		r = dup2(oldfd, newfd);
	if (r < 0)
		perror("minishell: dup2");
	return (r);
}

int	x_close(int fd)
{
	if (fd < 0)
		return (0);
	if (retry_close(fd) < 0)
	{
		perror("minishell: close");
		return (-1);
	}
	return (0);
}

void	close_if_open(int *fd)
{
	if (!fd || *fd < 0)
		return ;
	(void)retry_close(*fd);
	*fd = -1;
}
