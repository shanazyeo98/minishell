/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:28:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/07 17:16:56 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_grp(t_token *token, int basegrp)
{
	int	grp;

	grp = token->grp;
	while (token != NULL && token->grp > basegrp)
	{
		if (token->grp < grp)
			grp = token->grp;
		token = token->next;
	}
	return (grp);
}

t_ast	*parse(t_token *token, int grp)
{
	int		grp_min;
	t_ast	*branch;
	t_ast	*branch_cpy;

	grp_min = ret_grp(token, grp);
	branch = createbranch(token, grp_min);
	branch_cpy = branch;
	while (branch_cpy->type == OP)
	{
		if (branch_cpy->right == NULL)
		{
			branch_cpy->right = parse(ret_token(branch_cpy->id, token), branch_cpy->grp);
		}
		if (branch_cpy->left == NULL)
			break ;
		branch_cpy = branch_cpy->left;
	}
	if (branch_cpy->type == OP && branch_cpy->left == NULL)
	{
		branch_cpy->left = parse(token, branch_cpy->grp);
	}
	return (branch);
}
