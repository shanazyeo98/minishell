/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:09 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/24 19:27:03 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: copies n bytes from memory area src to memory area dst
Return: returns the original value of dst
Restrict (Type Qualifier): no other pointer will be used to access the object
*/

#include "libft.h"

void	*ft_memcpy(void *d, const void *src, size_t n)
{
	size_t	a;
	char	*dstring;
	char	*srcstring;

	if (d == NULL && src == NULL)
		return (NULL);
	a = 0;
	dstring = (char *) d;
	srcstring = (char *) src;
	while (a < n)
	{
		dstring[a] = srcstring[a];
		a++;
	}
	return (d);
}
