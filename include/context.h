/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:47:17 by seokson           #+#    #+#             */
/*   Updated: 2025/10/16 23:48:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

#include "env.h"

typedef struct s_ctx
{
	t_env	*env;
	int		last_status;
}	t_ctx;

#endif
