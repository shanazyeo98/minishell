/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:18:50 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:36 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_precision_assign(int input, int p, char *s)
{
	int			index;
	int			inputlen;
	long int	long_input;

	inputlen = ft_intlen(input);
	index = 1;
	long_input = (long) input;
	if (input < 0)
	{
		long_input *= -1;
		inputlen--;
	}
	while (index <= inputlen && p > 0)
	{
		s[p - index] = long_input % 10 + '0';
		long_input = long_input / 10;
		index++;
	}
	s[p] = '\0';
}

char	*ft_precision(int precision, int input, int precision_s)
{
	char	*str;
	int		len;
	int		input_len;

	input_len = ft_intlen(input);
	len = input_len;
	if (input < 0)
		len--;
	if (precision_s == 1 && input == 0 && precision == 0)
		len = 0;
	else if (precision > len)
		len = precision;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memset(str, '0', len);
	ft_precision_assign(input, len, str);
	return (str);
}

char	*ft_int(t_format *s, int input)
{
	int		max;
	char	*output;
	char	*number_str;
	char	*minwidth_str;
	int		prefixsign;

	prefixsign = 0;
	if (input < 0)
		prefixsign = 4;
	else if (s->sign == 1)
		prefixsign = 1;
	else if (s->blank == 1)
		prefixsign = 2;
	number_str = ft_precision(s->precision_no, input, s->precision);
	if (number_str == NULL)
		return (NULL);
	max = ft_strlen(number_str);
	minwidth_str = ft_width(s->min_width - max, s->zero, prefixsign);
	if (minwidth_str == NULL)
		return (NULL);
	output = ft_combine(number_str, minwidth_str, s->left, prefixsign);
	return (output);
}
