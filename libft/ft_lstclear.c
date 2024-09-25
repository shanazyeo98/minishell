/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:06:57 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/25 16:54:12 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Deletes and frees the given node and every successor of that node
Pointer to the list must be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*current_node;

	if (*lst != NULL)
	{
		current_node = *lst;
		while (current_node != NULL)
		{
			next_node = current_node->next;
			del(current_node->content);
			free(current_node);
			current_node = next_node;
		}
		*lst = NULL;
	}
}
