/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:11:57 by seunbaek          #+#    #+#             */
/*   Updated: 2025/10/18 12:33:18 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell_signal.h"
#include "loop.h"
#include "env.h"
#include "libft.h"
#include "context.h"

int	main(int ac, char **av, char **ev)
{
	int		ret;
	// char	*prompt;
	t_ctx	ctx;

	(void)ac;
	(void)av;
	ctx.env = env_from_environ(ev);
	ctx.last_status = 0;
	// prompt = make_prompt(ctx);
	set_signals_parent();
	ret = loop(&ctx);
	// free(prompt);
	rl_clear_history();
	env_free(&ctx.env);
	return (ret);
}
