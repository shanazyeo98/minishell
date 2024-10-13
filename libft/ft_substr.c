/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:54 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/13 15:58:42 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Create a substring from string s from start with max len
Return: Pointer to the substring*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	new_strlen;
	size_t	i;

	new_strlen = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		new_strlen = 0;
	if (new_strlen < len)
	{
		substring = malloc((new_strlen + 1) * sizeof(char));
		len = new_strlen;
	}
	else
		substring = malloc((len + 1) * sizeof(char));
	i = 0;
	if (substring != NULL)
	{
		while (i < len)
		{
			substring[i] = s[start + i];
			i++;
		}
		substring[i] = '\0';
	}
	return (substring);
}
