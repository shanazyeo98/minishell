/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:22:30 by mintan            #+#    #+#             */
/*   Updated: 2024/10/05 13:37:31 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Desription: Prints out the tokens as well as the characteristics given a
   token list. This function is used for general debugging.
*/

void	print_token_list(t_minishell ms)
{
	t_token	*curr_token;

	curr_token = *(ms.tokenlist);

	while (curr_token != NULL)
	{
		printf("Content: %s | Type: %d | Grp: %d | Word Grp: %d\n", \
		curr_token->str, curr_token->type, curr_token->grp, \
		curr_token->wordgrp);
		curr_token = curr_token->next;
	}
}
