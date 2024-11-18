/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_money.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:05:33 by mintan            #+#    #+#             */
/*   Updated: 2024/11/18 23:21:02 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: extracts a substring of the input based on the start and end
   index. The substring is addded into the content of a node in a linked list.
   The linked list node is returned.
*/

t_list	*get_split(int start, int end, char *input)
{
	t_list	*node;
	char	*content;
	int		len;

	len = end - start + 1;
	content = ft_substr(input, start, len);
	if (content == NULL)
		return (NULL);
	node = ft_lstnew(content);
	if (node == NULL)
		return (free(content), NULL);
	return (node);
}


/* Description: generates a node with "" if the input string is "". Returns a
   NULL if there are malloc errors.
*/

t_list	*gen_emptystr_node(void)
{
	t_list	*split;
	char	*content;

	content = ft_strdup("");
	if (content == NULL)
		return (NULL);
	split = ft_lstnew(content);
	return (split);
}

/* Description: function to find the starting index for splitting up the word.
   This function is only used when are no consecutive $$. Populates the start
   and end index into the given addresses.
*/

void	get_strt_end_idx(char *str, int *strt_idx, int *end_idx)
{
	if (str[*strt_idx] == '$')
		*strt_idx = *strt_idx + 1;
	*end_idx = *strt_idx;
	while ((str[*end_idx + 1] != '$') && (str[*end_idx + 1] != '\0'))
		*end_idx = *end_idx + 1;
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
   Returns: a linked list containing all the split members
*/

t_list	*split_money(char *str)
{
	t_money	mon;
	t_list	*node;

	mon.start = 0;
	if (ft_strlen(str) == 0)
	{
		mon.split = gen_emptystr_node();
		if (mon.split == NULL)
			return (NULL);
	}
	else
		mon.split = NULL;
	while (str[mon.start] != '\0')
	{
		if (str[mon.start] == '$' && \
		((str[mon.start + 1] == '$') || (str[mon.start + 1] == '\0')))
			mon.end = mon.start;
		else
			get_strt_end_idx(str, &mon.start, &mon.end);
		node = get_split(mon.start, mon.end, str);
		if (node == NULL)
			return (ft_lstclear(&(mon.split), &free), NULL);
		ft_lstadd_back(&(mon.split), node);
		mon.start = mon.end + 1;
	}
	return ((mon.split));
}
