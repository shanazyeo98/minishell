/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:17:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 16:37:56 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//functions for when there is no open token

int	checkend(t_minishell *params, t_tokendets *info)
{
	t_token	*last;

	last = lsttoken(*(params->tokenlist));
	if (info->status == OPEN && (last->type == DOUBLE || last->type == SINGLE))
		return (ERROR);
	if (last->type == OPERATOR || last->type == REDIRECTOR)
		return (ERROR);
	if (last->prev != NULL && last->grp < last->prev->grp)
		return (ERROR);
	return (SUCCESS);
}

int	checkparenthesis(t_tokendets *info, t_minishell *params)
{
	t_token	*token;
	int		count;

	token = *(params->tokenlist);
	count = 0;
	while (token != NULL)
	{
		if (token->grp == info->grp)
			count++;
		token = token->next;
	}
	if (count == 0)
		return (ERROR);
	return (checkend(params, info));
}

/*Description: Updates the word groups / groups based on whether the char
is a space or parenthesis.
If open parenthesis is called without a preceding operator, error
If group goes negative (i.e. close bracket without corresponding open), error*/
int	editgrps(char a, t_tokendets *tokeninfo, t_minishell *params)
{
	t_token	*lst;

	lst = lsttoken(*(params->tokenlist));
	if (a == ' ')
		tokeninfo->wordgrp++;
	else if (a == '(')
	{
		if (*(params->tokenlist) == NULL || ret_op(lst->str) == OR || \
		ret_op(lst->str) == AND)
			tokeninfo->grp++;
		else
			return (ERROR);
	}
	else
	{
		if (checkparenthesis(tokeninfo, params) == ERROR)
			return (ERROR);
		tokeninfo->grp--;
	}
	if (tokeninfo->grp < 0)
		return (ERROR);
	return (SUCCESS);
}

/*Description: For token type = operator / redirector
Operator: If preceding is null or operator, error
Redirector: If preceding is redirector, error*/
int	checkpreced(t_minishell *params, int type)
{
	t_token	*preceding;

	if (params->tokenlist == NULL)
		preceding = NULL;
	else
		preceding = lsttoken(*(params->tokenlist));
	if (type == OPERATOR)
	{
		if (preceding == NULL || preceding->type == OPERATOR)
			return (ERROR);
	}
	if (preceding != NULL && preceding->type == REDIRECTOR)
		return (ERROR);
	return (SUCCESS);
}

/*Description: Determines the new token to be created / connector
and executes the corresponding actions*/
int	newtoken(char a, t_minishell *params, t_tokendets *info, int i)
{
	int	type;

	if (chartype(a, params) == CONNECTOR)
	{
		if (editgrps(a, info, params) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	type = returntype(a, params);
	if (type == OPERATOR || type == REDIRECTOR)
	{
		if (checkpreced(params, type) == ERROR)
			return (ERROR);
	}
	if (assigntoken(type, info, params) == FAIL)
		return (FAIL);
	info->status = OPEN;
	info->start_i = i;
	if (type == SINGLE || type == DOUBLE)
		info->start_i++;
	return (SUCCESS);
}
