/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:04:13 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:56 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printc(char *str, t_format *spec, int count)
{
	if (spec->min_width > 1)
	{
		while (count < spec->min_width)
		{
			ft_putchar_fd(str[count], 1);
			count++;
		}
	}
	else
	{
		count = 1;
		ft_putchar_fd(str[0], 1);
	}
	return (count);
}

int	ft_print(char *str, t_format *spec)
{
	int		count;

	count = 0;
	if (spec->specifier == 'c')
	{
		count = ft_printc(str, spec, count);
	}
	else
	{
		ft_putstr_fd(str, 1);
		count = ft_strlen(str);
	}
	if (str != NULL)
		free(str);
	free(spec);
	return (count);
}

int	ft_conversion(int i, const char *input, va_list *ptr, int *count)
{
	int			index_p;
	t_format	*specifiers;
	char		*str;

	index_p = i;
	i++;
	specifiers = malloc(sizeof(t_format));
	ft_structinit(specifiers);
	if (ft_speccheck(input[i]) == 0)
		i = ft_formatspec(input, specifiers, ptr, i);
	if (ft_speccheck(input[i]) != 0)
	{
		specifiers->specifier = input[i];
		str = ft_format(specifiers, ptr);
		*count += ft_print(str, specifiers);
	}
	else
	{
		free(specifiers);
		ft_putchar_fd('%', 1);
		*count += 1;
		i = index_p;
	}
	return (i);
}

int	ft_loop(const char *input, va_list *ptr)
{
	int		overall_count;
	int		*count_ptr;
	int		index;

	overall_count = 0;
	count_ptr = &overall_count;
	index = 0;
	while (input[index] != '\0')
	{
		if (input[index] == '%')
		{
			index = ft_conversion(index, input, ptr, count_ptr);
		}
		else
		{
			ft_putchar_fd(input[index], 1);
			overall_count++;
		}
		index++;
	}
	return (overall_count);
}

int	ft_printf(const char *input, ...)
{
	va_list	arg_ptr;
	int		count;

	va_start(arg_ptr, input);
	count = ft_loop(input, &arg_ptr);
	va_end(arg_ptr);
	return (count);
}
