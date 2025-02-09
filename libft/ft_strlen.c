/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/17 19:27:06 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns the length of the string

#include "libft.h"

size_t	ft_strlen(const char *a)
{
	size_t	length;

	if (a == NULL)
		return (0);
	length = 0;
	while (*a != '\0')
	{
		length++;
		a++;
	}
	return (length);
}
