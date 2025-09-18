/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:11:26 by seokson           #+#    #+#             */
/*   Updated: 2025/09/17 14:33:25 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "ast.h"
# include "exec.h"
# include "sys/types.h"

typedef struct s_pipe
{
	int		prev_in;
	int		made;
	int		remain;
	pid_t	last_pid;
	t_env	*env;
}	t_pipe;

#endif
