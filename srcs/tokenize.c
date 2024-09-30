/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 13:32:15 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to continue working on:
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
	if (checkarray(params->operator, a) == exitstat(SUCCESS))
		return (character(OPERATOR));
	if (checkarray(params->redirector, a) == exitstat(SUCCESS))
		return (character(REDIRECTOR));
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
	return(token(BASIC));
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
			if (status != exitstat(SUCCESS))
				return (status);
			i++;
		}
		else
		{
			status = readchar(prompt[i], params, &info, &i);
			if (status != exitstat(SUCCESS))
				return (status);
		}
	}
}

int	main(void)
{
	t_minishell	params;

	declarearray(&params);
}
