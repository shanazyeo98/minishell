/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:30:03 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/09 17:49:10 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char(t_format *s, int input)
{
	char			*char_str;
	unsigned char	input_c;
	int				index;

	input_c = (unsigned char) input;
	if (s->min_width < 1)
		s->min_width = 1;
	char_str = malloc((s->min_width + 1) * sizeof(char));
	if (char_str == NULL)
		return (NULL);
	if (s->zero == 1)
		ft_memset(char_str, '0', s->min_width + 1);
	else
		ft_memset(char_str, ' ', s->min_width + 1);
	if (s->left == 1)
		index = 0;
	else
		index = s->min_width - 1;
	char_str[index] = input_c;
	char_str[s->min_width] = '\0';
	return (char_str);
}
