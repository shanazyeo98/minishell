/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:02:14 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/11 13:02:18 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include <stdio.h>

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

/*Description: Handles error or failures from tokenizing.
Fail: Free memory and exits out of minishell
Error: Free tokenlist and prints error message*/
void	tokenstatus(t_minishell *params, int status)
{
	if (status == FAIL)
		spick_and_span(params, FAIL);
	else if (status == ERROR)
		ft_putendl_fd(ERR_SYNTAX, 2);
	if (status == ERROR || *(params->tokenlist) == NULL)
		spick_and_span(params, ERROR);
}

/*Description: Initialises the token list and the info*/
void	inittokenlist(t_minishell *params, t_tokendets *info, char *prompt)
{
	info->prompt = prompt;
	info->status = CLOSED;
	info->wordgrp = 0;
	info->grp = 0;
	info->id = 0;
	params->hdcount = 0;
	params->tokenlist = malloc(sizeof(t_token *));
	if (params->tokenlist == NULL)
	{
		//clean up function
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		exit(FAIL);
	}
	*(params->tokenlist) = NULL;
}

/*Description: Start of the tokenizing module
Initialises the token info variables and determines the action based on the
status of the token & prompt*/
void	tokenize(char *prompt, t_minishell *params)
{
	int			i;
	t_tokendets	info;
	int			status;

	i = 0;
	inittokenlist(params, &info, prompt);
	status = SUCCESS;
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
			break ;
	}
	if (status == SUCCESS)
		status = endofprompt(params, &info, i);
	tokenstatus(params, status);
}
