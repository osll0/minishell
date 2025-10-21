/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:00:39 by seokson           #+#    #+#             */
/*   Updated: 2025/10/17 02:08:22 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "libft.h"
#include "prompt.h"

char	*pr_safe_dup(const char *s)
{
	if (s == NULL)
		return (ft_strdup(""));
	return (ft_strdup(s));
}

void	pr_append_lit(char **dst, const char *lit)
{
	char	*base;
	char	*joined;

	if (*dst == NULL)
		base = ft_strdup("");
	else
		base = ft_strdup(*dst);
	if (base == NULL)
		base = ft_strdup("");
	if (lit == NULL)
		joined = ft_strjoin(base, "");
	else
		joined = ft_strjoin(base, lit);
	free(*dst);
	free(base);
	*dst = joined;
	if (*dst == NULL)
		*dst = ft_strdup("");
}

void	pr_append_take(char **dst, char *frag)
{
	char	*base;
	char	*joined;

	if (*dst == NULL)
		base = ft_strdup("");
	else
		base = ft_strdup(*dst);
	if (base == NULL)
		base = ft_strdup("");
	if (frag == NULL)
		joined = ft_strjoin(base, "");
	else
		joined = ft_strjoin(base, frag);
	free(*dst);
	free(base);
	free(frag);
	*dst = joined;
	if (*dst == NULL)
		*dst = ft_strdup("");
}

char	*pr_tilde_path(const char *cwd, const char *home)
{
	size_t		hlen;
	const char	*rest;

	if (cwd == NULL)
		return (pr_safe_dup(""));
	if (home == NULL || *home == '\0')
		return (pr_safe_dup(cwd));
	hlen = strlen(home);
	if (hlen > 0 && strncmp(cwd, home, hlen) == 0)
	{
		rest = cwd + hlen;
		if (*rest == '\0')
			return (ft_strdup("~"));
		if (*rest == '/')
			return (ft_strjoin("~", rest));
	}
	return (pr_safe_dup(cwd));
}

char	*pr_resolve_cwd(t_ctx *ctx)
{
	char		*cwd;
	const char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		return (cwd);
	if (ctx != NULL)
		pwd = env_get(ctx->env, "PWD");
	else
		pwd = env_get(NULL, "PWD");
	if (pwd == NULL || *pwd == '\0')
		return (ft_strdup("."));
	return (ft_strdup(pwd));
}
