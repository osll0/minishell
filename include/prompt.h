/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokson <seokson@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 01:52:21 by seokson           #+#    #+#             */
/*   Updated: 2025/10/17 02:16:10 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "context.h"

char	*pr_safe_dup(const char *s);
void	pr_append_lit(char **dst, const char *lit);
void	pr_append_take(char **dst, char *frag);
char	*pr_tilde_path(const char *cwd, const char *home);
char	*pr_resolve_cwd(t_ctx *ctx);

char	*make_prompt(t_ctx *ctx);

#endif
