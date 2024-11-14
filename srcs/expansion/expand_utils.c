/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/11/14 08:13:15 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: checks if a character is a special character and hence not a
   valid variable name
   Returns:
	- TRUE: if the char is not in the special character list
	- FALSE: if the char is in the special character list
*/

int	check_special(char c)
{
	if ((c >= ' ' && c <= '#') || (c >= '%' && c <= '/') || \
	(c >= ':' && c <= '@') || (c >= '[' && c <= '^') || \
	(c >= '{' && c <= '~'))
		return (TRUE);
	return (FALSE);
}

/* Description: takes in a linked list where the contents are strings and joins
   all of the strings together. Outputs the joined string. Outputs NULL if there
   are malloc errors.
*/

char	*strjoin_llist(t_list *lst)
{
	t_list	*curr;
	char	*res;
	char	*temp;

	curr = lst;
	res = NULL;
	while (curr != NULL)
	{
		temp = ft_strjoin(res, (char *)curr->content);
		if (res != NULL)
			free (res);
		if (temp == NULL)
			return (NULL);
		res = ft_strdup(temp);
		free (temp);
		if (res == NULL)
			return (NULL);
		curr = curr->next;
	}
	return (res);
}


/* Description: Splits a string when "$$" is encountered. Each component is
   stored in a linked list. if there are no "$$", the original string is stored
   in one node in the linked list.
   E.g.:
	- "$$" -> "$", "$"
	- "123$$456$$789" -> "123$", "$456$", "$789"
	- "123" -> "123"
	- "123$$" -> "123$", "$"
	- "123$$$" -> "123$", "$", "$"
*/

t_list	*split_money(char *str)
{
	int	strt_idx;
	int	end_idx;

	strt_idx = 0;
	while (str[strt_idx] != '\0')
	{
		
	}
}


// int	main(void)
// {
// 	t_list	*n1;
// 	t_list	*n2;
// 	t_list	*curr;
// 	char	*result;

// 	n1 = ft_lstnew(ft_strdup("node 1"));
// 	n2 = ft_lstnew(ft_strdup("node 2"));
// 	ft_lstadd_back(&n1, n2);
// 	// curr = n1;
// 	// while (curr != NULL)
// 	// {
// 	// 	printf("%s\n", (char *)curr->content);
// 	// 	curr = curr->next;
// 	// }
// 	result = strjoin_llist(n1);
// 	printf("Result: %s\n", result);
// }
