/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:28:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/15 14:16:47 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Retrieves the smallest group relative to the basegrp in
a set of tokens*/

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

/*Description: Start of parsing module.
Creates branch based on the group and loops through node to build other
branches accordingly*/

t_ast	*parse(t_token *token, int grp)
{
	t_ast	*branch;
	t_ast	*cpy;

	branch = createbranch(token, grp);
	if (branch == NULL)
		return (NULL);
	cpy = branch;
	while (cpy->type == OP)
	{
		if (cpy->right == NULL)
			cpy->right = parse(ret_token(cpy->id, token), cpy->grp);
		if (cpy->right == NULL)
			return (free_tree(branch), NULL);
		if (cpy->left == NULL)
			break ;
		cpy = cpy->left;
	}
	if (cpy->type == OP)
	{
		cpy->left = parse(token, cpy->grp);
		if (cpy->left == NULL)
			return (free_tree(branch), NULL);
	}
	return (branch);
}
