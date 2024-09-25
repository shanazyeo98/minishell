/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:38:03 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/20 17:47:45 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Writes n zeroed bytes to the string s. If n is 0, do nothing*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	a;
	char	*s_string;

	s_string = (char *) s;
	a = 0;
	while (a < n)
	{
		s_string[a] = 0;
		a++;
	}
}
