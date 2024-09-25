/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:07:39 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/28 15:28:20 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Example: s1 = "abcstrangaba"
set = "ab"
result = "strang"
*/

#include "libft.h"

static int	ft_checkset(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index_s1;
	int		start_index;
	int		end_index;
	char	*result;

	index_s1 = 0;
	while (s1[index_s1] != '\0' && ft_checkset(s1[index_s1], set) == 1)
	{
		index_s1++;
	}
	start_index = index_s1;
	index_s1 = ft_strlen(s1) - 1;
	while (index_s1 != 0 && ft_checkset(s1[index_s1], set) == 1)
	{
		index_s1--;
	}
	end_index = index_s1 + 1;
	result = ft_substr(s1, start_index, end_index - start_index);
	return (result);
}
