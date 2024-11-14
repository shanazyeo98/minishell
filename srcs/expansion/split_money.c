/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_money.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:05:33 by mintan            #+#    #+#             */
/*   Updated: 2024/11/14 16:15:08 by mintan           ###   ########.fr       */
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
	int		strt_idx;
	int		end_idx;
	t_list	*split;
	t_list	*node;

	strt_idx = 0;
	split = NULL;
	while (str[strt_idx] != '\0')
	{
		if (str[strt_idx] == '$' && \
		((str[strt_idx + 1] == '$') || (str[strt_idx + 1] == '\0')))
			end_idx = strt_idx;
		else
		{
			if (str[strt_idx] == '$')
				strt_idx++;
			end_idx = strt_idx;
			while ((str[end_idx + 1] != '$') && (str[end_idx + 1] != '\0'))
				end_idx++;
		}
		node = get_split(strt_idx, end_idx, str);
		if (node == NULL)
			return (ft_lstclear(&split, &free), NULL);
		ft_lstadd_back(&split, node);
		strt_idx = end_idx + 1;
	}
	return (split);
}



// int	main(void)
// {
// 	char		*i1;
// 	char		*i2;
// 	char		*i3;
// 	char		*i4;
// 	char		*i5;
// 	char		*i6;
// 	char		*i7;
// 	char		*i8;

// 	t_list		*l1;
// 	t_list		*l2;
// 	t_list		*l3;
// 	t_list		*l4;
// 	t_list		*l5;
// 	t_list		*l6;
// 	t_list		*l7;
// 	t_list		*l8;


// 	i1 = ft_strdup("$");
// 	i2 = ft_strdup("$ ");
// 	i3 = ft_strdup("$USER");
// 	i4 = ft_strdup("$$$$$$ $USER $");
// 	i5 = ft_strdup("USER$$456$?$v2");
// 	i6 = ft_strdup("$& $USER$LANG nodolar");
// 	i7 = ft_strdup("123456");
// 	i8 = ft_strdup("$ $USER");


// 	l1 = split_money(i1);
// 	printf("l1\n");
// 	while (l1 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l1->content);
// 		l1 = l1->next;
// 	}
// 	l2 = split_money(i2);
// 	printf("l2\n");
// 	while (l2 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l2->content);
// 		l2 = l2->next;
// 	}
// 	l3 = split_money(i3);
// 	printf("l3\n");
// 	while (l3 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l3->content);
// 		l3 = l3->next;
// 	}
// 	l4 = split_money(i4);
// 	printf("l4\n");
// 	while (l4 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l4->content);
// 		l4 = l4->next;
// 	}
// 	l5 = split_money(i5);
// 	printf("l5\n");
// 	while (l5 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l5->content);
// 		l5 = l5->next;
// 	}
// 	l6 = split_money(i6);
// 	printf("l6\n");
// 	while (l6 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l6->content);
// 		l6 = l6->next;
// 	}
// 	l7 = split_money(i7);
// 	printf("l7\n");
// 	while (l7 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l7->content);
// 		l7 = l7->next;
// 	}
// 	l8 = split_money(i8);
// 	printf("l8\n");
// 	while (l8 != NULL)
// 	{
// 		printf("'%s'\n", (char *)l8->content);
// 		l8 = l8->next;
// 	}
// }
