/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipes_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:08:45 by seokson           #+#    #+#             */
/*   Updated: 2025/09/08 10:11:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_utils.h"

int	pipes_create(int n, int (*pipes)[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		if (x_pipe(pipes[i]) < 0)
		{
			j = 0;
			while (j < i)
			{
				close_pipe_pair(pipes[j]);
				j++;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	pipes_close_all(int n, int (*pipes)[2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		close_pipe_pair(pipes[i]);
		i++;
	}
}
