/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:23:10 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/09 17:58:44 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Checks if character is a closing character for the open token*/
int	checkifending(char a, t_minishell *params, t_token *opentoken)
{
	if (opentoken->type == SINGLE && a == '\'')
		return (SUCCESS);
	if (opentoken->type == DOUBLE && a == '"')
		return (SUCCESS);
	if (opentoken->type == OPERATOR)
	{
		if (chartype(a, params) != OPERATION)
			return (SUCCESS);
	}
	if (opentoken->type == REDIRECTOR)
	{
		if (chartype(a, params) != REDIRECTION)
			return (SUCCESS);
	}
	if (opentoken->type == BASIC)
	{
		if (a == '\'' || a == '"' || chartype(a, params) != OTHERS)
			return (SUCCESS);
	}
	return (ERROR);
}

/*Description: Closes the token by assigning the str and setting status to
closed*/
int	closetoken(t_tokendets *info, int i, t_token *open)
{
	open->str = ft_substr(info->prompt, info->start_i, i - info->start_i);
	if (open->str == NULL)
		return (FAIL);
	info->status = CLOSED;
	return (SUCCESS);
}

/*Description: If token is operator or redirector, check if it is valid
e.g. '&' is not valid*/
int	checkvalidopre(char *str, t_minishell *params)
{
	int	i;

	i = 0;
	while ((params->validopre)[i] != NULL)
	{
		if (ft_strcmp(str, (params->validopre)[i]) == 0)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

/*Description: Based on the open token, check if the token can be closed
If so, close and check if it is valid. Single & Double will increment i
Else, increment i
Returns error if closed token is not valid*/
int	readchar(char a, t_minishell *params, t_tokendets *info, int *i)
{
	t_token	*open;

	open = lsttoken(*(params->tokenlist));
	if (checkifending(a, params, open) == SUCCESS)
	{
		if (closetoken(info, *i, open) == FAIL)
			return (FAIL);
		if (open->type == OPERATOR || open->type == REDIRECTOR)
		{
			if (checkvalidopre(open->str, params) == ERROR)
				return (ERROR);
		}
		if (open->type == SINGLE || open->type == DOUBLE)
			(*i)++;
		if (heredoccheck(params) != SUCCESS)
			return (CANCEL);
	}
	else
		(*i)++;
	return (SUCCESS);
}
