/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:48:03 by mintan            #+#    #+#             */
/*   Updated: 2024/11/03 14:04:26 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description: Allocates with malloc(3) and returns a combined path.
   Joins 's1' and 's2' with a '/'
   - s1: prefix
   - s2: suffix
*/

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*intermediate_path;
	char	*combined_path;

	intermediate_path = ft_strjoin(s1, "/");
	if (intermediate_path == NULL)
		return (NULL);
	combined_path = ft_strjoin(intermediate_path, s2);
	free(intermediate_path);
	return (combined_path);
}
