/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 18:19:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//notes: $ cannot be alone in double quotes and basic
//brackets must have a token inside

//next steps:
//test with operators and the different error cases. implement the above.

//character matching functions
int	checkarray(char *array, char a)
{
	int	i;

	i = 0;
	while (array[i] != '\0')
	{
		if (a == array[i])
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	chartype(char a, t_minishell *params)
{
	if (checkarray(params->connector, a) == SUCCESS)
		return (CONNECTOR);
	if (checkarray(params->operator, a) == SUCCESS)
		return (OPERATION);
	if (checkarray(params->redirector, a) == SUCCESS)
		return (REDIRECTION);
	return (OTHERS);
}

int	returntype(char a, t_minishell *params)
{
	if (a == '\'')
		return(SINGLE);
	else if (a == '"')
		return(DOUBLE);
	else if (chartype(a, params) == OPERATION)
		return(OPERATOR);
	else if (chartype(a, params) == REDIRECTION)
		return(REDIRECTOR);
	return(BASIC);
}

//end of string function

int	endofprompt(t_minishell *params, t_tokendets *info, int i)
{
	t_token *last;

	if (info->grp != 0)
		return (ERROR);
	last = lsttoken(*(params->tokenlist));
	if (last == NULL)
		return (SUCCESS);
	if (last->type == BASIC)
		closetoken(info, i, last);
	if (info->status == OPEN && (last->type == DOUBLE || last->type == SINGLE))
		return (ERROR);
	if (last->type == OPERATOR || last->type == REDIRECTOR)
		return (ERROR);
	return (SUCCESS);
}

//main functions

int	tokenize(char *prompt, t_minishell *params)
{
	int	i;
	t_tokendets	info;
	int	status;

	info.prompt = prompt;
	info.status = CLOSED;
	info.wordgrp = 0;
	info.grp = 0;
	i = 0;
	while (prompt[i] != '\0')
	{
		if (info.status == CLOSED)
		{
			status = newtoken(prompt[i], params, &info, i);
			if (status != SUCCESS)
				return (status);
			i++;
		}
		else
		{
			status = readchar(prompt[i], params, &info, &i);
			if (status != SUCCESS)
				return (status);
		}
	}
	if (endofprompt(params, &info, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	main(void)
{
	t_minishell	params;
	int	status;

	declarearray(&params);
	params.tokenlist = malloc(sizeof(t_token *));
	*(params.tokenlist) = NULL;
	status = tokenize("(", &params);
	printf("%d\n", status);
}
