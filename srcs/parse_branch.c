/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:57:18 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 17:17:56 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	assignops(t_ast **branch, t_token *token, int grp)
//{
//	while (token != NULL)
//	{
//		if (token->type == OPERATOR)
//			//create operator node
//	}
//}

t_ast	**createbranch(t_minishell *params, int grp)
{
	t_ast	**branch;
	t_token	*token;

	branch = malloc(sizeof(t_ast *));
	if (branch == NULL)
		return (NULL);
	*branch = NULL;
	token = lsttoken(*(params->tokenlist));
}
