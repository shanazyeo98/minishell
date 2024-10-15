/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:20:27 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/15 14:16:23 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Frees cmd node and its ast node*/

void	freecmdnode(t_ast *node)
{
	int	i;

	if (node->cmd->args != NULL)
		ft_freearray(node->cmd->args);
	if (node->cmd->redir != NULL)
	{
		while ((node->cmd->redir)[i] != NULL)
		{
			if (((node->cmd->redir)[i])->file != NULL)
				free(((node->cmd->redir)[i])->file);
			free((node->cmd->redir)[i]);
			i++;
		}
		free(node->cmd->redir);
	}
	free(node->cmd);
	free(node);
}

/*Description: Frees the node in a tree*/

void	free_tree(t_ast *node)
{
	t_ast	*next;

	while (node != NULL && node->type == OP)
	{
		if (node->right != NULL && (node->right)->type == OP)
			free_tree(node->right);
		else if (node->right != NULL && (node->right)->type == CMD)
			freecmdnode(node->right);
		next = node->left;
		free(node);
		node = next;
	}
	if (node != NULL)
		freecmdnode(node);
}

/*Description: Frees the nodes in a branch*/

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
