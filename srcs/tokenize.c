/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/01 14:20:27 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//brackets must have a token inside
//next steps:
//test with operators and the different error cases. implement the above.

//end of string function

/*Description: To handle the end of prompt.
If status is open and last token is a basic token, to close the token
Else if status is open and last token is double or single, error
If last token is a redirector or operator, error*/
int	endofprompt(t_minishell *params, t_tokendets *info, int i)
{
	t_token	*last;

	if (info->grp != 0)
		return (ERROR);
	last = lsttoken(*(params->tokenlist));
	if (last == NULL)
		return (SUCCESS);
	if (last->type == BASIC && info->status == OPEN)
		closetoken(info, i, last);
	if (info->status == OPEN && (last->type == DOUBLE || last->type == SINGLE))
		return (ERROR);
	if (last->type == OPERATOR || last->type == REDIRECTOR)
		return (ERROR);
	return (SUCCESS);
}

//main functions

/*Description: Start of the tokenizing module
Initialises the token info variables and determines the action based on the
status of the token & prompt*/
int	tokenize(char *prompt, t_minishell *params)
{
	int			i;
	t_tokendets	info;
	int			status;

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
			i++;
		}
		else
			status = readchar(prompt[i], params, &info, &i);
		if (status != SUCCESS)
			return (status);
	}
	if (endofprompt(params, &info, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/*Description: Testing main for the tokenize function */
int	main(void)
{
	t_minishell	params;
	int			status;

	declarearray(&params);
	params.tokenlist = malloc(sizeof(t_token *));
	*(params.tokenlist) = NULL;
	status = tokenize("< && inputfile", &params);
	printf("%d\n", status);
}
