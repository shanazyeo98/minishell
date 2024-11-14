/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_money.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:05:33 by mintan            #+#    #+#             */
/*   Updated: 2024/11/14 13:31:44 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"







/* Description: given a string
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

	UPDATE YOUR DESCRIPTION LATER
	generate a linked list of contents that will undergo expansion
*/

t_list	**split_money(char *str)
{
	int		strt_idx;
	int		end_idx;
	t_list	**split;
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
			while ((str[end_idx + 1] != '$') || (str[end_idx + 1] != '\0'))
				end_idx++;
		}
		node = get_split(strt_idx, end_idx, str);
		//error handling here
		ft_lstadd_back(split, node);
		//start -> strt_idx
		//end -> end_idx
		strt_idx = end_idx + 1;
	}
	return (split);
}



int	main(void)
{
	char	*in1;
	char	*in2;
	char	*in3;
	char	*in4;

	in1 = ft_strdup("$");
	in2 = ft_strdup("$");






}
