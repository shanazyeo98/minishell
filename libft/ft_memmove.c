/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:00:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/20 16:20:57 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Copies len bytes from src to dst. Two strings may overlap
Return: Original value of dst*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	a;
	char	*srcstring;
	char	*dststring;

	srcstring = (char *) src;
	dststring = (char *) dst;
	if (srcstring < dststring && (srcstring + len) >= dststring)
	{
		a = 1;
		while (a <= len)
		{
			dststring[len - a] = srcstring[len - a];
			a++;
		}
	}
	else
		ft_memcpy(dststring, srcstring, len);
	return (dst);
}
