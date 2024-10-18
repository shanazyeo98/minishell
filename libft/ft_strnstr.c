/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/13 13:12:02 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*locate a substring in a string
returns the first occurrence of the null-terminated string_small in string_big
not more than len characters are searched
characters after a '\0' character are not searched*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_i;
	size_t	small_i;
	size_t	fail_count;

	big_i = 0;
	small_i = 0;
	fail_count = 0;
	while (big_i < len && big[big_i] != '\0' && little[small_i] != '\0')
	{
		if (big[big_i] == little[small_i])
		{
			small_i++;
			big_i++;
		}
		else
		{
			fail_count++;
			small_i = 0;
			big_i = fail_count;
		}
	}
	if (little[small_i] == '\0')
		return ((char *) big + (big_i - ft_strlen(little)));
	return (NULL);
}
