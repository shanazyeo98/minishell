/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:20:27 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/08 16:07:32 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freecmdnode(t_ast *node)
{
	free(node->cmd);
	free(node);
}

void	tree_error(t_ast *node)
{
	t_ast	*next;

	while (node != NULL && node->type == OP)
	{
		if (node->right != NULL && (node->right)->type == OP)
			tree_error(node->right);
		else if (node->right != NULL && (node->right)->type == CMD)
			freecmdnode(node->right);
		next = node->left;
		free(node);
		node = next;
	}
	if (node != NULL)
		freecmdnode(node);
}

void	branch_error(t_ast *branch)
{
	t_ast	*next;

	while (branch != NULL && branch->type == OP)
	{
		if (branch->right != NULL)
			freecmdnode(branch->right);
		next = branch->left;
		free(branch);
		branch = next;
	}
	if (branch != NULL)
		freecmdnode(branch);
}
