/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:02:36 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/28 15:59:52 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*concatenates string - appends the NUL-terminated string src to the end of
dst. it will append at most size - strlen(dst) - 1 byte, NUL-terminating the
result
Returns the initial length of dst plus length of src
Thought process documented in goodnotes*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	a;
	size_t	srclen;

	dstsize = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size < dstsize + 1)
		return (size + srclen);
	if (size == dstsize + 1)
		return (srclen + dstsize);
	a = 0;
	while (a < (size - dstsize - 1) && a < srclen)
	{
		dst[dstsize + a] = src[a];
		a++;
	}
	dst[dstsize + a] = '\0';
	return (srclen + dstsize);
}
