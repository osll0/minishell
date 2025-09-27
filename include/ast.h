/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunbaek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:41:14 by seunbaek          #+#    #+#             */
/*   Updated: 2025/09/18 16:32:40 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_tok { T_WORD, T_PIPE, T_LT, T_GT, T_DGT, T_HERE }	t_tok;
typedef enum e_redir_kind { R_IN, R_OUT, R_APP, R_HERE }	t_redir_kind;
typedef enum e_node { N_CMD, N_PIPE }	t_node_type;

typedef struct s_redir {
	t_redir_kind	kind;
	char			*target;
	int				quoted;
	int				here_fd;
	int				ambig;
}	t_redir;

typedef struct s_cmd {
	char	**argv;
	t_redir	*redirs;
	int		argc;
	int		n_redirs;
}	t_cmd;

typedef struct s_ast {
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			cmd;
}	t_ast;
#endif
