/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:16:19 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 12:51:35 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/* Descriptions: takes in a node and clones the contents of the node using
   ft_strdup into a new node. Returns a NULL if any malloc fails
*/
t_list	*clone_node(t_list *node)
{
	t_list	*clone;
	char	*content;

	content = ft_strdup((char *)node->content);
	if (content == NULL)
		return (NULL);
	clone = ft_lstnew(content);
	if (clone == NULL)
	{
		free (content);
		return (NULL);
	}
	return (clone);
}

/* Description: takes in a linked list and node. Inserts the node in the ASCII
   sorted position in the linked list
*/
void	insert_sort_node(t_list **lst, t_list *node)
{
	t_list	*curr;

	if (*lst == NULL)
		ft_lstadd_back(lst, node);
	else if (ft_strcmp(node->content, (*lst)->content) < 0)
		ft_lstadd_front(lst, node);
	else
	{
		curr = *lst;
		while (curr->next != NULL && \
		ft_strcmp(node->content, curr->next->content) >= 0)
			curr = curr->next;
		ft_lstadd_node(curr, node);
	}
}

/* Description: Takes in an unsorted linked list and outputs a new linked list.
   The new linked list is sorted in ASCII order based on the contents of the
   linked list. If there are any malloc errors, the function frees the memory
   allocated within the function and returns a NULL
*/

t_list	*ft_lstsort(t_list **lst)
{
	t_list	*curr;
	t_list	*new;
	t_list	*add;

	// new = clone_node(*lst);
	// if (new == NULL)
		// return (NULL);
	new = NULL;

	curr = *lst;

	// curr = (*lst)->next;
	while (curr != NULL)
	{
		add = clone_node(curr);
		if (add == NULL)
		{
			ft_lstclear(&new, free);
			return (NULL);
		}
		insert_sort_node(&new, add);
		curr = curr->next;
	}
	return (new);
}

int	main(void)
{
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;
	t_list	*n4;
	t_list	*n5;

	t_list	*curr;
	t_list	*sorted;

	n1 = ft_lstnew(ft_strdup("n4"));
	n2 = ft_lstnew(ft_strdup("n3"));
	n3 = ft_lstnew(ft_strdup("n11"));
	n4 = ft_lstnew(ft_strdup("n1"));
	n5 = ft_lstnew(ft_strdup("n5"));


	ft_lstadd_back(&n1, n2);
	ft_lstadd_back(&n1, n3);
	ft_lstadd_back(&n1, n4);
	ft_lstadd_back(&n1, n5);


	printf("==========Before lstsort==========\n");
	curr = n1;
	while (curr != NULL)
	{
		printf("Node: %s\n", (char *)curr->content);
		curr = curr->next;
	}

	printf("==========After lstsort==========\n");
	sorted = ft_lstsort(&n1);
	curr = sorted;

	while (curr != NULL)
	{
		printf("Node: %s\n", (char *)curr->content);
		curr = curr->next;
	}
	return (0);
}
