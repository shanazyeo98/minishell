/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:42:53 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:49 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str(t_format *s, const char *input)
{
	char	*output;
	char	*str_str;
	int		maxlen;
	char	*minwidth_str;

	if (input == NULL)
	{
		input = "(null)";
		if (s->precision_no < 6 && s->precision == 1)
			s->precision_no = 0;
	}
	if (s->precision_no < (int) ft_strlen(input) && s->precision == 1)
		str_str = ft_substr(input, 0, s->precision_no);
	else
		str_str = ft_strdup(input);
	if (str_str == NULL)
		return (NULL);
	maxlen = ft_strlen(str_str);
	minwidth_str = ft_width(s->min_width - maxlen, s->zero, 0);
	if (minwidth_str == NULL)
		return (NULL);
	output = ft_combine(str_str, minwidth_str, s->left, 0);
	return (output);
}
