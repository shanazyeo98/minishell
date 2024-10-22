/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 09:05:06 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: finds the index of the first instance of c in str. Returns -1
   if c is not found
*/

int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* Description: Takes in an node from the envp linked list and copies the var
   name into a new node. The variable name is retrieved by finding the position
   of '=' in the envp node content and finding the substring before it
*/
t_list	*extract_and_copy_node(t_list *node)
{
	t_list	*copy;
	char	*content;

	content = ft_substr(node->content, 0, find_index(node->content, '='));
	if (content == NULL)
		return (NULL);
	copy = ft_lstnew(content);
	if (copy == NULL)
	{
		free (content);
		return (NULL);
	}
	return (copy);
}


/* Description: Takes in the envp list and clones a new linked list with only
   the variable name as the content. Returns a new linked list
*/

t_list	**clone_envp(t_list **envp)
{
	t_list	**exp;
	t_list	*curr;



}

