/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 14:31:33 by mintan           ###   ########.fr       */
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


/* Description: Takes in the envp list and clones a new temporary linked list
   with only the variable name as the content. A new ASCII-sorted linked list
   based on the temporary linked list is then created. The temporary linked
   list is freed. Returns the sorted new linked list.
*/

t_list	*clone_envp(t_list **envp)
{
	t_list	*tmp;
	t_list	*curr;
	t_list	*add;
	t_list	*exp;

	tmp = NULL;
	curr = *envp;
	while (curr != NULL)
	{
		add = extract_and_copy_node(curr);
		if (add == NULL)
		{
			ft_lstclear(&tmp, free);
			return (NULL);
		}
		ft_lstadd_back(&tmp, add);
		curr = curr->next;
	}
	exp = ft_lstsort(&tmp);
	ft_lstclear(&tmp, free);
	if (exp == NULL)
		return (NULL);
	return (exp);
}

/* Description: Takes in 2 arguments:
	- Arg 1: ASCII sorted linked list of environment variable names
	- Arg 2: Linked list of environment variables
   For each node in Arg 1, retrieve the variable value from Arg 2 and print out
   in the format of the bash commmand: export. Skips the var "_". Returns a
   status at the end of the execution
*/

int	export_print(t_list **sorted, t_list **envp)
{
	char	*varlue;
	t_list	*curr;
	int		status;

	status = SUCCESS;
	curr = *sorted;
	varlue = NULL;
	while (curr != NULL)
	{
		if (ft_strcmp((char *)curr->content, "_") != 0)
		{
			varlue = retrieve_env_var((char *)curr->content, *envp, &status);
			if (status == ERROR)
				return (ERROR);
			printf("declare -x ");
			printf("%s=\"%s\"\n", (char *)curr->content, varlue);
			free (varlue);
			varlue = NULL;
		}
		curr = curr->next;
	}
	return (SUCCESS);
}

/* Description: prints out the environment variables if ther e

*/

int	builtin_export(char **arg, t_list **envp)
{
	t_list	*sorted;

	if (countexeargs(arg) == 1)
	{
		sorted = clone_envp(envp);
		if (sorted == NULL)
			return (ERROR);
		export_print(&sorted, envp);
		ft_lstclear(&sorted, free);
	}
	// else
	// {
	// go in envp list
	// find the matching node, and rm the node and add a new node into the linked list
	
	// }
	return (SUCCESS);
}
