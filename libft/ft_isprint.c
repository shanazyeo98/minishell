/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/21 11:54:05 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns non-zero if character is a printable character
else, returns 0*/

#include "libft.h"

int	ft_isprint(int a)
{
	if (a >= 32 && a <= 126)
		return (1);
	return (0);
}
