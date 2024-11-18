/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimspace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/19 00:29:50 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Trims the leading spaces in front of a given string and returns
   a substring of the input string. The input string is not freed. Returns a
   NULL if there are malloc errors. Remember to check if a NULL is returned
   when using this function.
*/
// #include <stdio.h>

#include "libft.h"

char	*ft_strtrimspace(char *in)
{
	char	*trim;
	size_t	len;
	int		i;

	len = ft_strlen(in);
	i = 0;
	while (in[i] != '\0' && ft_isspace(in[i]) == 1)
		i++;
	trim = ft_substr(in, i, len);
	return (trim);
}

// int	main(void)
// {
// 	char	*o1;
// 	char	*o2;
// 	char	*o3;

// 	o1 = ft_strtrimspace("");
// 	printf("o1: '%s'\n", o1);
// 	o2 = ft_strtrimspace("\t\n");
// 	printf("o2: '%s'\n", o2);
// 	o3 = ft_strtrimspace("\t\n works");
// 	printf("o3: '%s'\n", o3);
// 	free (o1);
// 	free (o2);
// 	free (o3);

// }
