/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:19 by mintan            #+#    #+#             */
/*   Updated: 2024/10/23 12:56:56 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description: Takes in 2 nodes, n1 and n2. n1 is an existing node in a linked
   list while n2 is the node to be joined to the linked list behind n1. The
   original node behind n1 is joined to the back of n2 instead. n2 must be a
   single node that does not have any node joined behind it. Otherwise, the
   node behind n2 will be lost after using this function.
*/

void	ft_lstadd_node(t_list *n1, t_list *n2)
{
	n2->next = n1->next;
	n1->next = n2;
}
