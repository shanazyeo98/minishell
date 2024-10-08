/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:04:59 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/08 17:26:41 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*createnode(int id, int type, int op, int grp)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->id = id;
	node->type = type;
	node->op = op;
	node->grp = grp;
	return (node);
}

t_ast	*lstleftnode(t_ast *node)
{
	if (node == NULL)
		return (NULL);
	while (node->left != NULL)
		node = node->left;
	return (node);
}

void	addleftnode(t_ast **branch, t_ast *new)
{
	t_ast	*lst;

	if (*branch == NULL)
		*branch = new;
	else
	{
		lst = lstleftnode(*branch);
		lst->left = new;
	}
}

void	adduppernode(t_ast **branch, t_ast *new)
{
	t_ast	*node;

	if (*branch == NULL)
		*branch = new;
	else
	{
		node = *branch;
		node->up = new;
		new->left = node;
		*branch = new;
	}
}
