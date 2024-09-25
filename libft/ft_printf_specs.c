/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:39:22 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:46 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Format Specifier: %[flags][width][.precision]specifier

int	ft_flags(char *content, t_format *formatnode, int index)
{
	while (content[index] == '#' || content[index] == ' ' || \
	content[index] == '+' || content[index] == '-' || content[index] == '0')
	{
		if (content[index] == '#')
			formatnode->alternate = 1;
		if (content[index] == ' ')
			formatnode->blank = 1;
		if (content[index] == '+')
			formatnode->sign = 1;
		if (content[index] == '-')
			formatnode->left = 1;
		if (content[index] == '0')
			formatnode->zero = 1;
		index++;
	}
	return (index);
}

int	ft_fwidth(char *c_content, t_format *node, int i, va_list *ptr)
{
	if (c_content[i] == '*')
	{
		node->min_width = va_arg(*ptr, int);
		i++;
	}
	else if (ft_isdigit(c_content[i]) != 0)
	{
		node->min_width = ft_atoi(c_content + i);
		i += ft_intlen(node->min_width);
	}
	return (i);
}

int	ft_fprecision(char *c_content, t_format *node, int i, va_list *p)
{
	if (c_content[i] == '.')
	{
		node->precision = 1;
		i++;
		if (c_content[i] == '*')
		{
			node->precision_no = va_arg(*p, int);
			i++;
		}
		else if (ft_isdigit(c_content[i]) != 0)
		{
			node->precision_no = ft_atoi(c_content + i);
			while (ft_isdigit(c_content[i]) != 0)
				i++;
		}
		if (node->precision_no < 0)
			node->precision = 0;
	}
	return (i);
}

int	ft_formatspec(const char *c, t_format *f, va_list *ptr, int i)
{
	char	*c_content;

	c_content = (char *) c;
	i = ft_flags(c_content, f, i);
	i = ft_fwidth(c_content, f, i, ptr);
	i = ft_fprecision(c_content, f, i, ptr);
	if (f->precision == 1 || f->left == 1)
		f->zero = 0;
	return (i);
}
