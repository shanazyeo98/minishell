/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:49:11 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/28 15:47:40 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*takes in a character to check if it is a digit
if it is a numeric character, return non-zero
if it is not, return 0 */

#include "libft.h"

int	ft_isdigit(int a)
{
	if (!(a >= '0' && a <= '9'))
	{
		return (0);
	}
	return (1);
}
