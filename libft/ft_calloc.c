/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:40 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/26 15:36:17 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function: Contiguous Memory Allocation. Create multiple blocks at the run
time of a program having the same size in the memory and initializes each
byte to 0
Return: Pointer to the allocated memory, NULL is error*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, count * size);
	return (ptr);
}
