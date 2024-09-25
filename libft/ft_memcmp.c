/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:10:42 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/25 16:00:22 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Compares s1 and s2. Assumed to be n bytes long
Returns:
1. If the strings are identical - 0
2. Else - Difference between the first two differing bytes
3. Zero Length strings - 0*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	a;

	if (n == 0)
		return (0);
	str1 = (char *) s1;
	str2 = (char *) s2;
	a = 0;
	while (a < n && str1[a] == str2[a])
	{
		a++;
	}
	if (a == n)
		a -= 1;
	return ((unsigned char) str1[a] - (unsigned char) str2[a]);
}
