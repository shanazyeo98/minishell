/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/11/15 09:01:36 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: checks if a character is a special character. This function is
   used to check the first character after $ if it is valid for expansion.
   Numbers are also considered as invalid as ${digit} is not expanded.
   Returns:
	- TRUE: if the char is in in the special character list
	- FALSE: if the char is not the special character list
*/

int	chk_dollar(char c)
{
	if ((c >= ' ' && c <= '#') || (c >= '%' && c <= '@') || \
	(c >= '[' && c <= '^') || (c >= '{' && c <= '~'))
		return (TRUE);
	return (FALSE);
}

/* Description: checks if a character is a special character. This function is
   used to check all the characters in the provided variable name
   Returns:
	- TRUE: if the char is in in the special character list
	- FALSE: if the char is not the special character list
*/

int	chk_invalid_var(char c)
{
	if ((c >= ' ' && c <= '#') || (c >= '%' && c <= '/') || \
	(c >= ':' && c <= '@') || (c >= '[' && c <= '^') || (c >= '{' && c <= '~'))
		return (TRUE);
	return (FALSE);
}

/* Description: Takes in an array of strings and converts them into a linked
   list. Each string is stored in the content of the linked list by using
   ft_strdup. The array of strings must be NULL terminated.
*/

t_list	*stray_to_llist(char **str)
{
	t_list	*llist;
	int		i;
	char	*content;

	if (*str == NULL)
		return (NULL);
	i = 1;
	content = ft_strdup(str[0]);
	if (content == NULL)
		return (NULL);
	llist = ft_lstnew(content);
	if (llist == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		content = ft_strdup(str[i]);
		if (content == NULL)
		{
			ft_lstclear(&llist, free);
			return (NULL);
		}
		ft_lstadd_back(&(llist), ft_lstnew(content));
		i++;
	}
	return (llist);
}

/* Description: frees the memory allocated for strings in an array of strings.
   Also frees the memory allocated for the array of strings. Takes in an array
   of strings and the last index of the array where memory was allocated for
   strings.
*/

void	free_stray(char **stray, int i)
{
	while (i > 0)
	{
		i--;
		free(stray[i]);
	}
	free(stray);
}

/* Description: takes in a linked list, where the content of each node is a
   string. Converts the contents of the linked list into an array of strings.
   The string array is NULL terminated. llist must not be a NULL. Check if
   llist is NULL before calling this function.
*/

char	**llist_to_stray(t_list *llist)
{
	char	**stray;
	t_list	*curr;
	int		i;

	stray = malloc((ft_lstsize(llist) + 1) * sizeof(char *));
	if (stray == NULL)
		return (NULL);
	curr = llist;
	i = 0;
	while (curr != NULL)
	{
		stray[i] = ft_strdup((char *)curr->content);
		if (stray[i] == NULL)
		{
			free_stray(stray, i);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	stray[ft_lstsize(llist)] = NULL;
	return (stray);
}
