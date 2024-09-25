/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:57 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/27 16:10:44 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns a pointer to the first occurrence of the character c in string s
line: 25 - as the output type and input type is different, explicitly cast
s as a (char *) to convert */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	char	c_char;

	c_char = (char) c;
	while (*s != '\0')
	{
		if (*s == c_char)
		{
			result = (char *) s;
			return (result);
		}
		s++;
	}
	if (c_char == '\0')
		return ((char *) s);
	return (NULL);
}
