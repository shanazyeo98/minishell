/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:51:53 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/28 16:00:00 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copies string, take the full size of the buffer and guarantee to NUL-
terminate the result (as long as the size is larger than 0)
If size is 0, the destination is not modified.
Byte for NUL should be included in size
Return: the total length of the string they tried to create, i.e. the size of
src */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size < 1)
		return (srclen);
	a = 0;
	while (a < size - 1 && a < srclen)
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = '\0';
	return (srclen);
}
