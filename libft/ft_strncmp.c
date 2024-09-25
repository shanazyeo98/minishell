/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:59:54 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/25 15:39:55 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*compares two strings s1 and s2
returns 0 if s1 and s2 are equal
a negative value if s1 is less than s2
a positive value if s1 is greater than s2
the n parameter only compares the first n bytes of s1 and s2*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;
	int		result;

	if (n == 0)
		return (0);
	a = 0;
	while ((a < n) && (s1[a] == s2[a]) && s1[a] != '\0')
	{
		a++;
	}
	if (a == n)
		a -= 1;
	result = (unsigned char) s1[a] - (unsigned char) s2[a];
	return (result);
}
