/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:31:51 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/25 11:52:15 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fills the first n bytes of the memory area pointed to by b with the constant
byte c */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	a;
	char	*string;

	a = 0;
	string = (char *) b;
	while (a < len)
	{
		string[a] = c;
		a++;
	}
	return (b);
}
