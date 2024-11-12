/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/11/13 06:17:43 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: Takes in a character (char followinga $) are special
   characters. These special characters will be interpreted literally and not
   be expanded.
   Returns:
	- TRUE: if the char is not in the special character list
	- FALSE: if the char is in the special character list
*/

int	check_dollar(char c)
{
	if ((c >= ' ' && c <= '#') || (c >= '%' && c <= '/') ||
	(c >= ':' && c < '?') || (c == '@') || (c >= '[' && c <= '^') || \
	(c >= '{' && c <= '~'))
		return (0);
	return (1);
}
