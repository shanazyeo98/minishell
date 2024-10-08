/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:32:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/06 18:17:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Counts how many redirectors there are in the a given set of
valid commands*/
void	redircount(t_token *token, t_cmd *cmd)
{
	while (token != NULL && token->type != OPERATOR)
	{
		if (token->type == REDIRECTOR)
			cmd->n_redir++;
		token = token->next;
	}
}

/*Description: Initializes a command node and stores the starting token
and ending token of the command*/
t_cmd	*createcmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	redircount(token, cmd);
	cmd->start = token;
	while (token != NULL && token->type != OPERATOR)
		token = token->next;
	cmd->end = token;
	return (cmd);
}
