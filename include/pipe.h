/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:11:26 by seokson           #+#    #+#             */
/*   Updated: 2025/10/18 20:05:38 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <sys/types.h>
# include "env.h"

typedef struct s_pipe
{
	int			prev_in;
	int			made;
	int			remain;
	pid_t		last_pid;
	t_env		*env;
	const t_ast	*root;
}	t_pipe;

#endif
