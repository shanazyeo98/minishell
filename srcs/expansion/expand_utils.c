/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/11/14 20:34:58 by mintan           ###   ########.fr       */
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
	if ((c >= ' ' && c <= '#') || (c >= '%' && c <= '@') || \
	(c >= '[' && c <= '^') || (c >= '{' && c <= '~'))
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

/* Description: initialises the pamex structure. Checks if the input starts
   with a $ and splits the input string by $ to generate a linked list where
   each member is individually expanded.
*/

void	init_pamex(char *input, t_pamex *px)
{
	px->first = FALSE;
	px->error = FALSE;
	if (input[0] == '$')
		px->first = TRUE;
	px->dollar = split_money(input);
	if (px->dollar == NULL)
		px->error = TRUE;
}

/* Description: expand node for special characters
   TAKES IN BLAH BLAH BLAH
*/

int	expand_specialchars(t_list *cur, t_list *dollar)
{
	char	*temp;

	temp = ft_strjoin("$", (char *)cur->content);
	if (temp == NULL)
		return (ft_lstclear(&(dollar), &free), FAIL);
	free (cur->content);
	cur->content = temp;
	return (SUCCESS);
}

/* Description: Generate the expanded string by combining all the nodes in the
   linked list
*/

char *join_expanded_str(t_list *lst)
{
	char	*res;

	res = strjoin_llist(lst);
	ft_lstclear(&(lst), &free);
	if (res == NULL)
		return (NULL);
	return (res);
}

/* Description: WRITE DESCRIPTION HERE FIRST
*/

int	expand_node(t_list *cur, t_list *dollar, int status, t_list *envp)
{
	if (((char *)cur->content)[0] == '?')
	{
		cur->content = replace_exit_status(cur->content, status);
		if (cur->content == NULL)
			return (ft_lstclear(&(dollar), &free), FAIL);
	}
	else if (check_special(((char *)cur->content)[0]) == TRUE)
	{
		if (expand_specialchars(cur, dollar) == FAIL)
			return (FAIL);
	}
	else
	{
		cur->content = find_and_replace_param(cur->content, envp, cur->content);
		if (cur->content == NULL)
			return (ft_lstclear(&(dollar), &free), FAIL);
	}
	return (SUCCESS);
}
