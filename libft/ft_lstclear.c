/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:06:57 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/19 10:04:27 by mintan           ###   ########.fr       */
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
