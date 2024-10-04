/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:32:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 23:38:00 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdparams(t_token *token, int *redir, int *args)
{
	while (token != NULL && token->type != OPERATOR)
	{
		if (token->type == REDIRECTOR)
		{
			*(redir)++;
			token = (token->next)->next;
		}
		else
		{
			(*args)++;
			token = token->next;
		}
	}
}

int	fillcmd(t_token *token, t_ast *node)
{
	t_cmd	*command;
	int		args;
	int		redir;

	command = malloc(sizeof(t_cmd));
	if (command == NULL)
		return (FAIL);
	args = 0;
	redir = 0;
	cmdparams(token, &redir, &args);
	//function to assign the values
}
