<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:11:57 by seunbaek          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:00 by seunbaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "signal.h"
#include "loop.h"
#include "env.h"

int	main(int ac, char **av, char **ev)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = env_fron_environ(ev);
	set_signals_parent();
	loop(env_list);
	env_free(&env_list);
	return (0);
}
