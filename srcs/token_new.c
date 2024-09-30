/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:17:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 12:22:28 by shayeo           ###   ########.fr       */
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
		if (params->tokenlist == NULL || \
		(lsttoken(*(params->tokenlist)))->type == token(OPERATOR))
			tokeninfo->grp++;
		else
			return (exitstat(ERROR));
	}
	else
		tokeninfo->grp--;
	if (tokeninfo->grp < 0)
		return (exitstat(ERROR));
	return (exitstat(SUCCESS));
}

int	checkpreced(t_minishell *params, int type)
{
	t_token *preceding;

	preceding = lsttoken(*(params->tokenlist));
	if (preceding->type == token(REDIRECTOR))
		return (exitstat(ERROR));
	if (type == token(OPERATOR))
	{
		if (preceding == NULL || preceding->type == token(OPERATOR))
			return (exitstat(ERROR));
	}
	return (exitstat(SUCCESS));
}

int	newtoken(char a, t_minishell *params, t_tokendets *info, int i)
{
	int type;

	if (chartype(a, params) == character(CONNECTOR))
	{
		if (editgrps(a, info, params) == exitstat(ERROR))
			return (exitstat(ERROR));
	}
	type = returntype(a, params);
	if (type == token(OPERATOR) || type == token(REDIRECTOR))
	{
		if (checkpreced(params, type) == exitstat(ERROR))
			return (exitstat(ERROR));
	}
	if (assigntoken(type, info, params) == exitstat(FAIL))
		return (exitstat(FAIL));
	info->status = OPEN;
	info->start_i = i;
	if (type == token(SINGLE) || type == token(DOUBLE))
		info->start_i++;
	return (exitstat(SUCCESS));
}
