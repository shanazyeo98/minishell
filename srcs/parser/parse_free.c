/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:20:27 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/29 15:34:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Function to clear redirect list*/

void	clearcmd(void *content)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *) content;
	ft_freearray(cmd->args);
	i = 0;
	if (cmd->redir != NULL)
	{
		while ((cmd->redir)[i] != NULL)
		{
			if (((cmd->redir)[i])->file != NULL)
				free(((cmd->redir)[i])->file);
			if ((cmd->redir)[i]->fd != -1)
				close((cmd->redir)[i]->fd);
			free((cmd->redir)[i]);
			i++;
		}
		free(cmd->redir);
	}
	free(cmd);
}

/*Description: Frees cmd node and its ast node*/

void	freecmdnode(t_ast *node)
{
	if (node->cmdnode->cmds != NULL)
		ft_lstclear(&node->cmdnode->cmds, &clearcmd);
	free(node->cmdnode);
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
