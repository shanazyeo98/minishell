/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:57:16 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:24 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_structinit(t_format *s)
{
	s->alternate = 0;
	s->blank = 0;
	s->left = 0;
	s->min_width = 0;
	s->precision = 0;
	s->precision_no = 0;
	s->sign = 0;
	s->specifier = '0';
	s->zero = 0;
}

char	*ft_prefix(int prefix)
{
	char	*prefixstr;

	if (prefix == 1)
		prefixstr = ft_strdup("+");
	if (prefix == 2)
		prefixstr = ft_strdup(" ");
	if (prefix == 3)
		prefixstr = ft_strdup("0x");
	if (prefix == 4)
		prefixstr = ft_strdup("-");
	if (prefix == 0)
		prefixstr = ft_strdup("");
	if (prefixstr == NULL)
		return (NULL);
	return (prefixstr);
}

char	*ft_width(int len, int zero, int prefix)
{
	char	*output;

	if (prefix > 0)
	{
		if (prefix == 3)
			len -= 2;
		else if (prefix == 1 || prefix == 2 || prefix == 4)
			len -= 1;
	}
	if (len < 0)
		len = 0;
	output = malloc((len + 1) * sizeof(char));
	if (zero == 1)
		ft_memset(output, '0', len);
	else
		ft_memset(output, ' ', len);
	output[len] = '\0';
	return (output);
}

char	*ft_combine(char *a, char *b, int left, int prefix)
{
	char	*output;
	char	*buffer;
	char	*prefixstr;

	prefixstr = ft_prefix(prefix);
	if (b[0] == '0' || left == 1)
	{
		if (b[0] == '0')
			buffer = ft_strjoin(b, a);
		else
			buffer = ft_strjoin(a, b);
		output = ft_strjoin(prefixstr, buffer);
	}
	else
	{
		buffer = ft_strjoin(prefixstr, a);
		output = ft_strjoin(b, buffer);
	}
	if (output == NULL || buffer == NULL)
		return (NULL);
	free(a);
	free(b);
	free(buffer);
	free(prefixstr);
	return (output);
}
