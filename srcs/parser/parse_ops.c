/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:04:59 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 16:37:28 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Creates a AST node*/

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
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*Description: Retrieves the last left node of a tree*/

t_ast	*lstleftnode(t_ast *node)
{
	if (node == NULL)
		return (NULL);
	while (node->left != NULL)
		node = node->left;
	return (node);
}

/*Description: Adds a node to the left of the tree*/

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

/*Description: Adds a upper node at the top of the tree*/

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
