/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:18:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/23 18:21:58 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	a;
	int		result;

	a = 0;
	while ((s1[a] == s2[a]) && s1[a] != '\0')
	{
		a++;
	}
	result = (unsigned char) s1[a] - (unsigned char) s2[a];
	return (result);
}
