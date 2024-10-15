/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:32:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/15 15:09:37 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Description: Initializes a command node and stores the starting token
and ending token of the command*/
t_cmd	*createcmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->start = token;
	while (token != NULL && token->type != OPERATOR)
		token = token->next;
	cmd->end = token;
	cmd->args = NULL;
	cmd->redir = NULL;
	return (cmd);
}
