/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_freecntnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:22:54 by mintan            #+#    #+#             */
/*   Updated: 2024/10/10 23:37:28 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description: Frees memory allocated to a memory location by taking in a
   pointer and using free(). This function is mainly passed into the
   ft_lstclear() function to delete the content in a linked list.
*/

void	ft_lst_freecntnt(void *ptr)
{
	free(ptr);
}
