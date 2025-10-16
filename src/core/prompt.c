/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 01:53:28 by seokson           #+#    #+#             */
/*   Updated: 2025/10/17 02:23:01 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "libft.h"
#include "prompt.h"

static char	*resolve_host(t_ctx *ctx)
{
	const char	*h;

	h = env_get(ctx->env, "HOSTNAME");
	if (!h || !*h)
		h = env_get(ctx->env, "NAME");
	if (h && *h)
		return (ft_strdup(h));
	return (ft_strdup("unknownhost"));
}

static char	*resolve_user(t_ctx *ctx)
{
	const char	*u;

	u = env_get(ctx->env, "USER");
	if (u == NULL || *u == '\0')
		u = env_get(ctx->env, "LOGNAME");
	if (u == NULL || *u == '\0')
		return (ft_strdup("user"));
	return (ft_strdup(u));
}

char	*make_prompt(t_ctx *ctx)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*path;
	char	*prompt;

	user = resolve_user(ctx);
	host = resolve_host(ctx);
	cwd  = pr_resolve_cwd(ctx);
	path = pr_tilde_path(cwd, env_get(ctx->env, "HOME"));
	prompt = ft_strdup("");
	if (user == NULL || host == NULL || path == NULL || prompt == NULL) {
		free(user);
		free(host);
		free(cwd);
		free(path);
		free(prompt);
		return (ft_strdup("minishell$ "));
	}
	pr_append_take(&prompt, user);
	pr_append_lit(&prompt, "@");
	pr_append_take(&prompt, host);
	pr_append_lit(&prompt, ":");
	pr_append_take(&prompt, path);
	pr_append_lit(&prompt, "$ ");
	free(cwd);
	return (prompt);
}
