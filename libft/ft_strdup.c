/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:33:45 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/30 11:51:43 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Allocates sufficient memory for a copy of the string s1
Return:
1. Pointer to the copy of the string
2. If insufficient memory is available, NULL is returned and errno is set
to ENOMEM*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_copy;
	int		s1_len;
	int		i;

	s1_len = ft_strlen(s1);
	s1_copy = malloc((s1_len + 1) * sizeof(char));
	if (s1_copy == NULL)
		return (s1_copy);
	i = 0;
	while (i < s1_len)
	{
		s1_copy[i] = s1[i];
		i++;
	}
	s1_copy[i] = '\0';
	return (s1_copy);
}
