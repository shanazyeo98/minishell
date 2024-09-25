/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/21 11:48:02 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns the length of the string

#include "libft.h"

size_t	ft_strlen(const char *a)
{
	size_t	length;

	length = 0;
	while (*a != '\0')
	{
		length++;
		a++;
	}
	return (length);
}
