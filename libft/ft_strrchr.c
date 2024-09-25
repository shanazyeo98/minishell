/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:41:51 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/27 16:12:27 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns a pointer to the last occurrence of the character c in string s
line: 27 - as the output type and input type is different, explicitly cast
s as a (char *) to convert
declaring result as a null pointer first to determine what to return*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	char	c_char;

	c_char = (char) c;
	result = NULL;
	while (*s != '\0')
	{
		if (*s == c_char)
		{
			result = (char *) s;
		}
		s++;
	}
	if (result != NULL)
		return (result);
	if (c_char == '\0')
		return ((char *) s);
	return (NULL);
}
