/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/10 16:46:47 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: Checks if a token requires expansion given a token. A token is
   eligible for expansion under the following conditions:
	1. Token contents start with '$' AND
	2. Token type is BASIC or DOUBLE
   Returns a TRUE or FALSE
*/

int	token_expand_eligibiility(t_token *tkn)
{
	if (tkn->str[0] == '$' && (tkn->type == BASIC || tkn->type == DOUBLE))
		return (TRUE);
	else
		return (FALSE);
}



/*
*/





