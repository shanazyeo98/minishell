/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:21:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/06/09 12:36:14 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: convert the integer to a string
Return:
1. The string
2. NULL if allocation fails*/

#include "libft.h"

int	ft_intlen(int n)
{
	int		count;

	count = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * -1;
		count += 1;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_minint(void)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (12));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '-';
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
	ptr[11] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*int_string;
	int		index;
	int		original_n;

	original_n = n;
	if (n == -2147483648)
		return (ft_minint());
	int_string = malloc((ft_intlen(original_n) + 1) * sizeof(char));
	if (int_string == NULL)
		return (int_string);
	index = 1;
	if (n < 0)
		n *= -1;
	while (index <= ft_intlen(original_n))
	{
		if (original_n < 0 && index == ft_intlen(original_n))
			int_string[ft_intlen(original_n) - index] = '-';
		else
			int_string[ft_intlen(original_n) - index] = (n % 10) + 48;
		n = n / 10;
		index++;
	}
	int_string[ft_intlen(original_n)] = '\0';
	return (int_string);
}
