/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:15:56 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/21 11:53:55 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*checks whether c is a 7-bit unsigned char value that fits into the ASCII
character set
returns non-zero if c is a 7-bit US-ASCII character between 0 and
octal 0177 inclusive
else returns zero
*/

#include "libft.h"

int	ft_isascii(int a)
{
	if (a >= 0 && a <= 127)
		return (1);
	return (0);
}
