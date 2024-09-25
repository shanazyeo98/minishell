/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:09:42 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/28 15:57:40 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Converts the initial portion of the string pointed to by nptr to int
Stops when it cannot recognise a character as a number
Accepts a single - or + at the start
Return: Converted value or 0 on error*/

#include "libft.h"

static int	ft_chartoi(const char a)
{
	int	i;

	i = a - '0';
	return (i);
}

static int	ft_atoitrim(const char *n)
{
	int	i;

	i = 0;
	while (n[i] == 32 || (n[i] >= 9 && n[i] <= 13))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	result;

	i = ft_atoitrim(nptr);
	sign = 1;
	result = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i += 1;
	}
	while (ft_isdigit(nptr[i]) != 0 && nptr[i] != '\0')
	{
		result = result * 10 + ft_chartoi(nptr[i]);
		i++;
	}
	return (result * sign);
}
