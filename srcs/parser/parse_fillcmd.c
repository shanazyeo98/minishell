/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:32:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 16:37:22 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Initializes a command node and stores the starting token
and ending token of the command*/
t_cmdnode	*createcmd(t_token *token)
{
	t_cmdnode	*node;

	node = malloc(sizeof(t_cmdnode));
	if (node == NULL)
		return (NULL);
	node->start = token;
	while (token != NULL && !(token->type == OPERATOR && ret_op(token->str) != PIPE))
		token = token->next;
	node->end = token;
	node->cmds = NULL;
	return (node);
}
