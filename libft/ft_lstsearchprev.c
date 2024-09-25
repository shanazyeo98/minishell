/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearchprev.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:30:17 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/10 14:30:40 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsearchprev(t_list *first, t_list *node)
{
	if (first == NULL)
		return (NULL);
	while (first->next != node)
		first = first->next;
	return (first);
}
