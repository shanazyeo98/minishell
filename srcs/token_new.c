/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:17:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 18:16:05 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//functions for when there is no open token

int	editgrps(char a, t_tokendets *tokeninfo, t_minishell *params)
{
	if (a == ' ')
		tokeninfo->wordgrp++;
	else if (a == '(')
	{
		if (*(params->tokenlist) == NULL || \
		(lsttoken(*(params->tokenlist)))->type == OPERATOR)
			tokeninfo->grp++;
		else
			return (ERROR);
	}
	else
		tokeninfo->grp--;
	if (tokeninfo->grp < 0)
		return (ERROR);
	return (SUCCESS);
}

int	checkpreced(t_minishell *params, int type)
{
	t_token *preceding;

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

int	newtoken(char a, t_minishell *params, t_tokendets *info, int i)
{
	int type;

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
