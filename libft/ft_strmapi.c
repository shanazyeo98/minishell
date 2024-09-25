/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:53:00 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/27 12:56:55 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Applies function f to each character of string s,
passing the index as the first argument and character itself as second
Return: New string is created after successful application of f
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*new_s;

	len = ft_strlen(s);
	new_s = malloc((len + 1) * sizeof(char));
	i = 0;
	if (new_s != NULL)
	{
		while (s[i] != '\0')
		{
			new_s[i] = f(i, s[i]);
			i++;
		}
		new_s[i] = '\0';
	}
	return (new_s);
}
