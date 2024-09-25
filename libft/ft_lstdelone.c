/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:52:26 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/27 14:16:43 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Frees the node but retain the next
Setting lst to null is to ensure that the garbage values are not assigned
and nothing is in lst
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	lst = NULL;
}
