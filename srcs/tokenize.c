/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/02 12:12:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
	return (checkend(params, info));
}

//main functions

void	inittokenlist(t_minishell *params)
{
	params->tokenlist = malloc(sizeof(t_token *));
	if (params->tokenlist == NULL)
	{
		//clean up function
		write(2, ERR_MALLOC_FAIL, 49);
		exit(FAIL);
	}
	*(params->tokenlist) = NULL;
}

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
	inittokenlist(params);
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
	return (endofprompt(params, &info, i));
}

//	if (endofprompt(params, &info, i) == ERROR)
//		return (ERROR);
//	return (SUCCESS);

/*Description: Testing main for the tokenize function */
/*int	main(void)
{
	t_minishell	params;
	int			status;

	declarearray(&params);
	params.tokenlist = malloc(sizeof(t_token *));
	*(params.tokenlist) = NULL;
	status = tokenize("echo ($)", &params);
	printf("%d\n", status);
}*/
