/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:22:30 by mintan            #+#    #+#             */
/*   Updated: 2024/11/19 18:09:00 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Desription: Prints out the tokens as well as the characteristics given a
   token list. This function is used for general debugging.
*/

// void	print_token_list(t_minishell ms)
// {
// 	t_token	*curr_token;

// 	curr_token = *(ms.tokenlist);
// 	while (curr_token != NULL)
// 	{
// 		printf("Content: %s | Type: %d | Grp: %d | Word Grp: %d\n", \
// 		curr_token->str, curr_token->type, curr_token->grp, \
// 		curr_token->wordgrp);
// 		curr_token = curr_token->next;
// 	}
// }

/*Description: Retrieves the first token in the wordgroup that is
not an operator or redirector*/

t_token	*ret_tokenwordgrp(int wordgrp, t_token *token)
{
	while (token != NULL)
	{
		if (token->type != OPERATOR && token->type != REDIRECTOR \
		&& token->wordgrp == wordgrp)
			return (token);
		token = token->next;
	}
	return (NULL);
}
