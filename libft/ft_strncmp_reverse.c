/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_reverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:56:00 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/27 17:12:53 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_reverse(char *s1, char *s2, int n)
{
	int	i_1;
	int	i_2;

	i_1 = ft_strlen(s1) - n;
	i_2 = ft_strlen(s2) - n;
	if (i_1 < 0 || i_2 < 0)
		return (-1);
	while (s1[i_1] == s2[i_2] && s1[i_1] != '\0')
	{
		i_1++;
		i_2++;
	}
	return ((unsigned char) s1[i_1] - (unsigned char) s2[i_2]);
}
