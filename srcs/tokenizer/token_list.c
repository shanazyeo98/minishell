/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:21:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/09 17:58:28 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Retrieves the last token in the token list.
NULL if it is empty*/
t_token	*lsttoken(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

/*Description: Frees the token list*/
void	freetokens(t_token **list)
{
	t_token	*token;
	t_token	*next;

	if (list != NULL && *list != NULL)
	{
		token = *list;
		while (token != NULL)
		{
			next = token->next;
			if (token->str != NULL)
				free(token->str);
			free(token);
			token = next;
		}
		free(list);
	}
}

/*Description: Creates and return a token object based on the values
provided*/
t_token	*createtoken(int type, t_tokendets *info)
{
	t_token	*newtoken;

	newtoken = malloc(sizeof(t_token));
	if (newtoken == NULL)
		return (NULL);
	newtoken->type = type;
	newtoken->wordgrp = info->wordgrp;
	newtoken->grp = info->grp;
	newtoken->str = NULL;
	newtoken->next = NULL;
	newtoken->prev = NULL;
	newtoken->id = info->id;
	info->id++;
	return (newtoken);
}

/*Description: Creates a token and assigns it to the back of the
token list.*/
int	assigntoken(int type, t_tokendets *info, t_minishell *params)
{
	t_token	*new;
	t_token	*last;

	new = createtoken(type, info);
	if (new == NULL)
		return (FAIL);
	last = lsttoken(*params->tokenlist);
	if (last == NULL)
		*(params->tokenlist) = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

t_token	*ret_token(int id, t_token *token)
{
	while (token != NULL)
	{
		if (token->id > id)
			break ;
		token = token->next;
	}
	return (token);
}
