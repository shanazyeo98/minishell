/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/29 18:06:25 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to continue working on:
// 1. newtoken function
// 2. tokenize function

//notes: $ cannot be alone in double quotes and basic
//brackets must have a token inside

//character matching functions
int	checkarray(char *array, char a)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (a == array[i])
			return (exitstat(SUCCESS));
		i++;
	}
	return (exitstat(ERROR));
}

int	chartype(char a, t_minishell *params)
{
	if (checkarray(params->connector, a) == exitstat(SUCCESS))
		return (character(CONNECTOR));
	return (character(OTHERS));
}

int	returntype(char a, t_minishell *params)
{
	if (a == '\'')
		return(token(SINGLE));
	else if (a == '"')
		return(token(DOUBLE));
	else if (chartype(a, params) == character(OPERATOR))
		return(token(OPERATOR));
	else if (chartype(a, params) == character(REDIRECTOR))
		return(token(REDIRECTOR));
	//remaining basic token and NIL
}

//splitting into tokens functions

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

int	newtoken(char a, t_minishell *params, t_tokendets *info, int i)
{
	int type;

	if (chartype(a, params) == character(CONNECTOR))
	{
		if (editgrps(a, info, params) == exitstat(ERROR))
			return (exitstat(ERROR));
	}
	//retrieve the type of token here
	//for operator and redirector, check if previous token is valid
	else
		return(exitstat(ERROR));
	if (assigntoken(type, info, params) == exitstat(FAIL))
		return (exitstat(FAIL));
	info->start_i = i;
	if (type == token(SINGLE) || type == token(DOUBLE))
		info->start_i++;
	return (exitstat(SUCCESS));
}

int	tokenize(char *prompt, t_minishell *params)
{
	int	i;
	t_tokendets	info;
	int	status;

	info.status = CLOSED;
	info.wordgrp = 0;
	info.grp = 0;
	i = 0;
	while (prompt[i] != '\0')
	{
		if (info.status == CLOSED)
		{
			status = newtoken(prompt[i], params, &info, i);
			if (status != exitstat(SUCCESS))
				return (status);
		}
		//function for where token is open
	}
}

int	main(void)
{
	t_minishell	params;

	//add a function to declare the type of arrays storing the various characters
	params.connector[0] = '(';
	params.connector[1] = ')';
	params.connector[2] = ' ';
	params.connector[3] = '\0';
}
