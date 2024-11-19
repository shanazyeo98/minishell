/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/19 15:15:51 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: returns 1 if the character c, is any of the following:
	-  9 (horizontal tab) <= c =< 13 (carriage return)
	- c == 32 (space)
   else, returns 0
*/

#include "libft.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c < 13) || c == 32)
		return (1);
	return (0);
}
