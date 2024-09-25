/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:13:24 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/21 11:53:41 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns non-zero if argument is an alphanumeric character
returns 0 if argument is neither an alphabet nor a digit */

#include "libft.h"

int	ft_isalnum(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}
