/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 01:53:28 by seokson           #+#    #+#             */
/*   Updated: 2025/10/18 12:08:30 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "env.h"
#include "libft.h"
#include "prompt.h"

static char	*get_hostname(void)
{
	int		fd;
	char	buf[1024];
	ssize_t	n;
	char	*tmp;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("unknownhost"));
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (ft_strdup("unknownhost"));
	buf[n] = '\0';
	tmp = ft_strchr(buf, '\n');
	if (tmp)
		*tmp = '\0';
	tmp = strchr(buf, '.');
	if (tmp)
		*tmp = '\0';
	return (ft_strdup(buf));
}

static char	*get_user(t_ctx *ctx)
{
	const char	*u;

	u = env_get(ctx->env, "USER");
	if (u == NULL || *u == '\0')
		u = env_get(ctx->env, "LOGNAME");
	if (u == NULL || *u == '\0')
		return (ft_strdup("user"));
	return (ft_strdup(u));
}

void	pr_append(char **prompt, char *user, char *host, char *path)
{
	pr_append_take(prompt, user);
	pr_append_lit(prompt, "@");
	pr_append_take(prompt, host);
	pr_append_lit(prompt, ":");
	pr_append_take(prompt, path);
	pr_append_lit(prompt, "$ ");
}

char	*make_prompt(t_ctx *ctx)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*path;
	char	*prompt;

	user = get_user(ctx);
	host = get_hostname();
	cwd = pr_resolve_cwd(ctx);
	path = pr_tilde_path(cwd, env_get(ctx->env, "HOME"));
	prompt = ft_strdup("");
	if (user == NULL || host == NULL || path == NULL || prompt == NULL)
	{
		free(user);
		free(host);
		free(cwd);
		free(path);
		free(prompt);
		return (ft_strdup("minishell$ "));
	}
	pr_append(&prompt, user, host, path);
	free(cwd);
	return (prompt);
}
