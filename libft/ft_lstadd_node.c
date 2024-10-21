/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:19 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 03:47:03 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

// int	main(void)
// {
// 	t_list	*n1;
// 	t_list	*n2;
// 	t_list	*n3;
// 	t_list	*n4;
// 	t_list	*n5;

// 	t_list	*curr;

// 	n1 = ft_lstnew(ft_strdup("n1"));
// 	n2 = ft_lstnew(ft_strdup("n2"));
// 	n3 = ft_lstnew(ft_strdup("n3"));
// 	n4 = ft_lstnew(ft_strdup("n4"));
// 	n5 = ft_lstnew(ft_strdup("n5"));


// 	ft_lstadd_back(&n1, n2);
// 	ft_lstadd_back(&n1, n3);
// 	ft_lstadd_back(&n1, n4);

// 	printf("==========Before lst_addnode==========\n");
// 	curr = n1;
// 	while (curr != NULL)
// 	{
// 		printf("Node: %s\n", (char *)curr->content);
// 		curr = curr->next;
// 	}

// 	printf("==========After lst_addnode==========\n");
// 	ft_lstadd_node(n4, n5);
// 	curr = n1;
// 	while (curr != NULL)
// 	{
// 		printf("Node: %s\n", (char *)curr->content);
// 		curr = curr->next;
// 	}
// 	return (0);
// }
