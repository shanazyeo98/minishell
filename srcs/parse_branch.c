/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:57:18 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 23:41:37 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assignops(t_ast **branch, t_token *token, int grp)
{
	t_ast	*newnode;

	while (token != NULL)
	{
		if (token->type == OPERATOR && token->grp == grp)
		{
			newnode = createnode(token->id, OP, ret_op(token->str), grp);
			if (newnode == NULL)
				return (FAIL);
			addleftnode(branch, newnode);
		}
		token = token->prev;
	}
	return (SUCCESS);
}

int	assigncmd(t_ast **branch, t_token *token, int grp)
{
	t_ast	*newnode;
	t_token	*cmdstart;

	while (token != NULL)
	{
		if (token->type == OPERATOR && token->grp == grp)
		{
			cmdstart = token->next;
			if (cmdstart->grp == grp)
			{
				newnode = createnode(cmdstart->id, CMD, NIL, cmdstart->grp);
				//filling of command function
			}
		}
	}
}

t_ast	**createbranch(t_minishell *params, int grp)
{
	t_ast	**branch;
	t_token	*token;

	branch = malloc(sizeof(t_ast *));
	if (branch == NULL)
		return (NULL);
	*branch = NULL;
	token = lsttoken(*(params->tokenlist));
	if (assignops(branch, token, grp) == FAIL)
	{
		//clean up branch
		return (NULL);
	}
	return (branch);
}
