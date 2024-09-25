/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:55:56 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:43 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptrlen(unsigned long int input)
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

void	ft_ptrstr(char	*str, unsigned long int input, int len)
{
	char	*ptrset;
	int		ptrlen;
	int		i;

	ptrset = "0123456789abcdef";
	ptrlen = ft_ptrlen(input);
	i = 1;
	while (i <= ptrlen && len != 0)
	{
		str[len - i] = ptrset[input % 16];
		input = input / 16;
		i++;
	}
	str[len] = '\0';
}

char	*ft_pprecision(int p, unsigned long int input, int p_s)
{
	char	*pstr;
	int		len;
	int		ptrlen;

	ptrlen = ft_ptrlen(input);
	if (p_s == 1 && p == 0 && input == 0)
		len = 0;
	else
	{
		if (p > ptrlen)
			len = p;
		else
			len = ptrlen;
	}
	pstr = malloc((len + 1) * sizeof(char));
	if (pstr == NULL)
		return (NULL);
	ft_memset(pstr, '0', len);
	ft_ptrstr(pstr, input, len);
	return (pstr);
}

char	*ft_pointer(t_format *s, void *ptr)
{
	unsigned long int	p;
	char				*phexstr;
	int					max;
	char				*minwidth_str;
	char				*output;

	p = (unsigned long int) ptr;
	if (p == 0)
		phexstr = ft_strdup("(nil)");
	else
		phexstr = ft_pprecision(s->precision_no, p, s->precision);
	if (phexstr == NULL)
		return (NULL);
	max = ft_strlen(phexstr);
	if (p == 0)
		minwidth_str = ft_width(s->min_width - max, s->zero, 0);
	else
		minwidth_str = ft_width(s->min_width - max, s->zero, 3);
	if (minwidth_str == NULL)
		return (NULL);
	if (p == 0)
		output = ft_combine(phexstr, minwidth_str, s->left, 0);
	else
		output = ft_combine(phexstr, minwidth_str, s->left, 3);
	return (output);
}
