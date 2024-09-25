/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:00 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:14 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_format(t_format *specifier, va_list *ptr)
{
	char	*new_str;

	if (specifier->specifier == 'd' || specifier->specifier == 'i')
		new_str = ft_int(specifier, va_arg(*ptr, int));
	else if (specifier->specifier == 'c')
		new_str = ft_char(specifier, va_arg(*ptr, int));
	else if (specifier->specifier == 's')
		new_str = ft_str(specifier, va_arg(*ptr, const char *));
	else if (specifier->specifier == 'u')
		new_str = ft_uint(specifier, va_arg(*ptr, int));
	else if (specifier->specifier == 'x' || specifier->specifier == 'X')
		new_str = ft_hex(specifier, va_arg(*ptr, int));
	else if (specifier->specifier == 'p')
		new_str = ft_pointer(specifier, va_arg(*ptr, void *));
	else
		new_str = ft_percentage();
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}
