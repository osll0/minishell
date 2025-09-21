/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:52:33 by seokson           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/20 17:24:08 by seokson          ###   ########.fr       */
=======
/*   Updated: 2025/09/20 14:54:38 by seokson          ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_split_free(char **v)
{
	int	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}
