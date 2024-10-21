/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:19 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 04:37:33 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description: Takes in a linked list and a node to be removed in the linked
   list. Performs the following behaviour depending on the position of the
   node to be removed:
	- Remove_Node is first node: pointer to the linked list is set as the
	  second node. Remove the Remove_Node afterwards
	- Remove_Node is in the middle of the linked list / final node of linked
	  list: the pointer following Remove_Node is joined to the preceding node.
	  Remove the Remove_Node afterwards
*/

void	ft_lstrm_node(t_list **lst, t_list	*rm_node)
{
	t_list	*start;

	if (*lst == rm_node)
	{
		start = rm_node->next;
		ft_lstdelone(rm_node, free);
		*lst = start;
	}
	else
	{
		start = *lst;
		while (start->next != rm_node)
			start = start->next;
		start->next = start->next->next;
		ft_lstdelone(rm_node, free);
	}
}
