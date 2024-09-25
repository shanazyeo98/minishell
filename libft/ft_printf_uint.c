/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:05 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:53 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uintlen(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_uintstr(char	*str, unsigned int input, int len)
{
	int		index;
	int		intlen;

	index = 1;
	intlen = ft_uintlen(input);
	while (index <= intlen && len != 0)
	{
		str[len - index] = input % 10 + '0';
		input = input / 10;
		index++;
	}
	str[len] = '\0';
}

char	*ft_uprecision(int precision, unsigned int input, int precision_s)
{
	char	*str;
	int		len;
	int		intlen;

	intlen = ft_uintlen(input);
	if (precision_s == 1 && precision == 0 && input == 0)
		len = 0;
	else
	{
		if (precision > intlen)
			len = precision;
		else
			len = intlen;
	}
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memset(str, '0', len);
	ft_uintstr(str, input, len);
	return (str);
}

char	*ft_uint(t_format *s, unsigned int input)
{
	int		max;
	char	*output;
	char	*number_str;
	char	*minwidth_str;

	number_str = ft_uprecision(s->precision_no, input, s->precision);
	if (number_str == NULL)
		return (NULL);
	max = ft_strlen(number_str);
	minwidth_str = ft_width(s->min_width - max, s->zero, 0);
	if (minwidth_str == NULL)
		return (NULL);
	output = ft_combine(number_str, minwidth_str, s->left, 0);
	return (output);
}
