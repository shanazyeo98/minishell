/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:06 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:30 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexlen(unsigned int input)
{
	int	i;

	i = 0;
	if (input == 0)
		i = 1;
	while (input > 0)
	{
		input = input / 16;
		i++;
	}
	return (i);
}

void	ft_upperhex(char *s)
{
	while (*s != '\0')
	{
		*s = ft_toupper(*s);
		s++;
	}
}

void	ft_hexstr(char	*str, unsigned int input, int len)
{
	char	*hexset;
	int		hexlen;
	int		i;

	hexset = "0123456789abcdef";
	hexlen = ft_hexlen(input);
	i = 1;
	while (i <= hexlen && len != 0)
	{
		str[len - i] = hexset[input % 16];
		input = input / 16;
		i++;
	}
	str[len] = '\0';
}

char	*ft_hprecision(int p, unsigned int input, int p_s)
{
	char	*hstr;
	int		len;
	int		hexlen;

	hexlen = ft_hexlen(input);
	if (p_s == 1 && p == 0 && input == 0)
		len = 0;
	else
	{
		if (p > hexlen)
			len = p;
		else
			len = hexlen;
	}
	hstr = malloc((len + 1) * sizeof(char));
	if (hstr == NULL)
		return (NULL);
	ft_memset(hstr, '0', len);
	ft_hexstr(hstr, input, len);
	return (hstr);
}

char	*ft_hex(t_format *s, unsigned int input)
{
	int		prefix;
	int		max;
	char	*phex_str;
	char	*minwidth_str;
	char	*output;

	phex_str = ft_hprecision(s->precision_no, input, s->precision);
	if (phex_str == NULL)
		return (NULL);
	max = ft_strlen(phex_str);
	prefix = 0;
	if (s->alternate == 1 && input != 0)
		prefix = 3;
	minwidth_str = ft_width(s->min_width - max, s->zero, prefix);
	if (minwidth_str == NULL)
		return (NULL);
	output = ft_combine(phex_str, minwidth_str, s->left, prefix);
	if (s->specifier == 'X')
		ft_upperhex(output);
	return (output);
}
