/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/23 12:57:46 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: Retrieves a variable name from an input string. Searches up to
   char c within the input string using ft_strchr. If 'c' does not exist within
   the input string, the whole string is the variable name. Uses a ft_strdup or
   ft_substr to return a variable name
*/

char	*get_var_name(char *in, char c)
{
	char	*var;

	if (ft_strchr(in, c) == NULL)
		var = ft_strdup(in);
	else
		var = ft_substr(in, 0, ft_strchr(in, c) - in);
	return (var);
}


/* Description: takes in an array of strings containing the environment
   variables and their corresponding values. For each environment variable,
   search through the envp linked list for a match and remove that node if
   there is a match. Add the whole string into the envp linked list after.
*/

int	add_var(t_list **envp, char **args)
{
	char	*var;
	int		i;
	t_list	*found;
	t_list	*add;

	i = 1;
	while (args[i] != NULL)
	{
		var = get_var_name(args[i], '=');
		if (var == NULL)
			return (FAIL);
		found = find_env_var(var, *envp);
		free (var);
		var = NULL;
		if (found != NULL)
			ft_lstrm_node(envp, found);
		var = ft_strdup(args[i]);
		if (var == NULL)
			return (FAIL);
		add = ft_lstnew(var);
		if (add == NULL)
			return (free (var), FAIL);
		ft_lstadd_back(envp, add);
		i++;
	}
	return (SUCCESS);
}
