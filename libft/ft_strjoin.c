/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:15:20 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/14 05:33:43 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Concatenates s1 and s2
Return: The new string
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstring;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	newstring = malloc((len + 1) * sizeof(char));
	if (newstring != NULL)
	{
		ft_strlcpy(newstring, s1, ft_strlen(s1) + 1);
		ft_strlcat(newstring, s2, len + 1);
	}
	return (newstring);
}

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*out;

	s1 = NULL;\
	s2 = " result";
	out = ft_strjoin(s1, s2);
	ft_printf("result: %s\n", out);
}
