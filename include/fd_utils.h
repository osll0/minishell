/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:30:29 by seokson           #+#    #+#             */
/*   Updated: 2025/09/09 22:31:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_UTILS_H
# define FD_UTILS_H

# include <sys/types.h>

int		x_open_ro(const char *path);
int		x_open_trunc(const char *path, mode_t mode);
int		x_open_append(const char *path, mode_t mode);

int		x_dup2(int oldfd, int newfd);
int		x_close(int fd);
void	close_if_open(int *fd);

int		x_pipe(int p[2]);
void	close_pipe_pair(int p[2]);

int		pipes_create(int n, int (*pipes)[2]);
void	pipes_close_all(int n, int (*pipes)[2]);

#endif
