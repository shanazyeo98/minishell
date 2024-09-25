/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:09:53 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/30 14:00:38 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Iterates the list and applies the function on the content
New list is created, freeing is done if any of the malloc fails.
*/

#include "libft.h"

static t_list	*ft_fail(t_list *firstnode, void (*del)(void *), void *content)
{
	free(content);
	ft_lstclear(&firstnode, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*next_node;
	t_list	*first_node;
	void	*content;

	if (lst == NULL)
		return (NULL);
	content = f(lst->content);
	if (content == NULL)
		return (NULL);
	first_node = ft_lstnew(content);
	if (first_node == NULL)
		return (ft_fail(first_node, del, content));
	lst = lst->next;
	while (lst != NULL)
	{
		content = f(lst->content);
		if (content == NULL)
			return (ft_fail(first_node, del, content));
		next_node = ft_lstnew(content);
		if (next_node == NULL)
			return (ft_fail(first_node, del, content));
		ft_lstadd_back(&first_node, next_node);
		lst = lst->next;
	}
	return (first_node);
}
