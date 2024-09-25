/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:23:52 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/25 15:42:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Locates the first occurrence of c within n bytes
Return: A pointer to the byte located, or NULL if does not exists*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s_string;
	char	c_char;
	size_t	a;

	c_char = (char) c;
	s_string = (char *) s;
	a = 0;
	while (a < n)
	{
		if (s_string[a] == c_char)
			return (s_string + a);
		a++;
	}
	return (NULL);
}
