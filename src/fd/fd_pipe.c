/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:06:33 by seokson           #+#    #+#             */
/*   Updated: 2025/09/08 10:08:31 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "fd_utils.h"

int	x_pipe(int p[2])
{
	int	r;

	r = pipe(p);
	while (r < 0 && errno == EINTR)
		r = pipe(p);
	if (r < 0)
		perror("minishell:pipe");
	return (r);
}

void	close_pipe_pair(int p[2])
{
	if (!p)
		return ;
	close_if_open(&p[0]);
	close_if_open(&p[1]);
}
