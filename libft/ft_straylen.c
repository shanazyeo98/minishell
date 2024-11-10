/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straylen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/03 16:45:00 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: returns the length of a NULL-terminated string array. The input
   string array MUST be NULL terminated. The length does not include the NULL
   member.
*/

#include "libft.h"

int	ft_straylen(char **stray)
{
	int	len;

	len = 0;
	while (stray[len] != NULL)
		len++;
	return (len);
}
