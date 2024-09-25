/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/21 11:53:49 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* from the manual: checks for an alphabetic character
returns zero if the parameter isn't an alphabet
returns non zero number if the parameter is an alphabet */

#include "libft.h"

int	ft_isalpha(int a)
{
	if (!((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z')))
	{
		return (0);
	}
	return (1);
}
