/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/11/15 12:40:35 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free (input);
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
   linked list. The input linked list is freed after the contents are joined.
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

/* Description: Given a node in a linked list, where the contents are a string
   to be expanded, perform variable expansion depending on the various
   scenarios. Frees the whole linked list if there are malloc errors
	- "?xxxx": string starts with ? -> replace ? with exit status
	- "$$$$": single $ or consecutive ? -> each dollar is printed literally
	- "~!@#$%^&*()_+{}| etc": special characters (excluding ?) and numbers ->
	   printed literally
	- "_asd": valid variable names -> look for matching variable value in the
	  envp list and replace the variable name:
	  	- Found: replace variable name with value
		- Not found: replace variable name with ""
*/

int	expand_node(t_list *cur, t_list *dollar, int status, t_list *envp)
{
	if (((char *)cur->content)[0] == '?')
	{
		cur->content = replace_exit_status(cur->content, status);
		if (cur->content == NULL)
			return (ft_lstclear(&(dollar), &free), FAIL);
	}
	else if (chk_dollar(((char *)cur->content)[0]) == TRUE)
	{
		if (expand_specialchars(cur, dollar) == FAIL)
			return (FAIL);
	}
	else
	{
		cur->content = find_n_replace_param(cur->content, envp, cur->content);
		if (cur->content == NULL)
			return (ft_lstclear(&(dollar), &free), FAIL);
	}
	return (SUCCESS);
}
