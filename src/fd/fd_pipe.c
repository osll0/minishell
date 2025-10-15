/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:06:33 by seokson           #+#    #+#             */
/*   Updated: 2025/10/06 16:21:02 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "fd_utils.h"

int	x_pipe(int p[2])
{
	while (1)
	{
		if (pipe(p) == 0)
			return (0);
		if (errno == EINTR)
			continue ;
		return (-1);
	}
}

void	close_pipe_pair(int p[2])
{
	if (!p)
		return ;
	close_if_open(&p[0]);
	close_if_open(&p[1]);
}
