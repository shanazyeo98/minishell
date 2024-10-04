/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:57:18 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 21:14:34 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_op(char *str)
{
	if (ft_strcmp(str, "&&") == 0)
		return (AND);
	if (ft_strcmp(str, "||") == 0)
		return (OR);
	return (PIPE);
}

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
