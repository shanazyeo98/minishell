/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:28:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/07 12:16:48 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_grp(t_token *token, int op)
{
	int	grp;

	grp = token->grp;
	if (op == MIN)
	{
		while (token != NULL)
		{
			if (token->grp < grp)
				grp = token->grp;
			token = token->next;
		}
	}
	if (op == MAX)
	{
		while (token != NULL)
		{
			if (token->grp > grp)
				grp = token->grp;
			token = token->next;
		}
	}
	return (grp);
}

void	assignbranch(t_ast **branch, t_ast **newbranch)
{
	int		id;
	t_ast	*node;

	if (*branch == NULL)
		*branch = *newbranch;
	else
	{
		id = (*newbranch)->id;
		node = *branch;
		while (node != NULL && node->type == OP)
		{
			if (node->id < id)
			node->right = *newbranch;
			node = node->left;
		}
	}
}

void	parse(t_minishell *params)
{
	int	grp_min;
	int	grp_max;
	t_ast	**branch;

	params->ast = malloc(sizeof(t_ast *));
	if (params->ast == NULL)
	{
		//clean up function
		exit(1);
	}
	*(params->ast) = NULL;
	grp_min = ret_grp(*(params->tokenlist), MIN);
	grp_max = ret_grp(*(params->tokenlist), MAX);
	while (grp_min <= grp_max)
	{
		branch = createbranch(params, grp_min);
		assignbranch(params->ast, branch);
		free(branch);
		grp_min++;
	}
}
