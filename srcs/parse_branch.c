/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:57:18 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/07 17:17:59 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assignops(t_ast **branch, t_token *token, int grp)
{
	t_ast	*newnode;

	while (token != NULL && token->grp >= grp)
	{
		if (token->type == OPERATOR && token->grp == grp)
		{
			newnode = createnode(token->id, OP, ret_op(token->str), grp);
			if (newnode == NULL)
				return (FAIL);
			adduppernode(branch, newnode);
		}
		token = token->next;
	}
	return (SUCCESS);
}

t_ast	*createcmdnode(t_token *cmdstart)
{
	t_ast	*newnode;

	newnode = createnode(cmdstart->id, CMD, NIL, cmdstart->grp);
	if (newnode == NULL)
		return (NULL);
	newnode->cmd = createcmd(cmdstart);
	if (newnode->cmd == NULL)
		return (free(newnode), NULL);
	return (newnode);
}

int	lstcmd(t_token *token, t_ast *node, t_ast **branch)
{
	t_ast *newnode;

	newnode = createcmdnode(token);
	if (newnode == NULL)
		return (FAIL);
	if (node == NULL)
		*branch = newnode;
	else
		node->left = newnode;
	return (SUCCESS);
}

int	assigncmd(t_ast **branch, t_token *token, int grp)
{
	t_ast	*node;
	t_token	*cmdstart;
	t_ast	*newnode;

	node = *branch;
	while (node != NULL)
	{
		cmdstart = ret_token(node->id, token);
		if (cmdstart->grp == grp)
		{
			newnode = createcmdnode(cmdstart);
			if (newnode == NULL)
				return (FAIL);
			node->right = newnode;
		}
		if (node->left == NULL)
			break ;
		node = node->left;
	}
	if (token->grp == grp)
		return (lstcmd(token, node, branch));
	return (SUCCESS);
}

t_ast	*createbranch(t_token *token, int grp)
{
	t_ast	*branch;

	branch = NULL;
	if (assignops(&branch, token, grp) == FAIL)
	{
		//clean up branch
		return (NULL);
	}
	if (assigncmd(&branch, token, grp) == FAIL)
	{
		//clean up branch
		return (NULL);
	}
	return (branch);
}
