/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eggcoffee <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:13:26 by eggcoffee         #+#    #+#             */
/*   Updated: 2025/10/14 17:13:46 by eggcoffee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

static void indent(int depth)
{
    while (depth--)
        printf("  ");
}

void print_ast(t_ast *node, int depth)
{
    int i;

    if (!node)
        return ;

    if (node->type == N_PIPE)
    {
        indent(depth);
        printf("[PIPE]\n");
        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
    }
    else if (node->type == N_CMD)
    {
        indent(depth);
        printf("[CMD]\n");
        for (i = 0; i < node->cmd.argc; i++)
        {
            indent(depth + 1);
            printf("argv[%d]: %s\n", i, node->cmd.argv[i]);
        }
        for (i = 0; i < node->cmd.n_redirs; i++)
        {
            indent(depth + 1);
            printf("redir[%d]: kind=%d, target=%s\n",
                i, node->cmd.redirs[i].kind,
                node->cmd.redirs[i].target ? node->cmd.redirs[i].target : "(null)");
        }
    }
}
