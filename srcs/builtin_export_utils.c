/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/24 16:48:18 by mintan           ###   ########.fr       */
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

/* Description: checks if the variable name is valid. Checks:
	1. Var name must start wtih '_' or a letter
	2. No '.', '-', ' '
   Returns ERROR (1) if the var name is invalid. Returns SUCCESS (0) otherwise
*/
int	check_var(char *var)
{
	int	i;

	if (var == NULL)
		return (FAIL);
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (ERROR);
	i = 1;
	while (var[i] != '\0')
	{
		if ((var[i] >= ' ' && var[i] <= '#') || \
		(var[i] >= '%' && var[i] <= '/') || \
		(var[i] >= ':' && var[i] <= '@') || \
		(var[i] >= '[' && var[i] <= '^') || \
		(var[i] >= '{' && var[i] <= '~'))
		{
			ft_putstr_fd(ERR, STDERR_FILENO);
			ft_putstr_fd(": export: ", STDERR_FILENO);
			ft_putstr_fd(var, STDERR_FILENO);
			ft_putendl_fd(" : Pick a better variable name. 1d10t", STDERR_FILENO);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

// /* Description: Retrieves the variable name from an input string and validates
//    the variable name. Return:
// 	- FAIL: malloc errors
// 	- ERROR: invalid var name
// */
// int	get_check_var(char *in)
// {
// 	char	*var;

// 	var = get_var_name(in, '=');
// 	if (var == NULL)
// 		return (FAIL);
// 	if (check_var(var) == ERROR)
// 	{
// 		ft_putstr_fd(ERR, STDERR_FILENO);
// 		ft_putstr_fd(": export: ", STDERR_FILENO);
// 		ft_putstr_fd(var, STDERR_FILENO);
// 		ft_putendl_fd(" : Pick a better variable name. 1d10t", STDERR_FILENO);
// 	}
// 	return (check_var(var));
// }



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
		if (check_var(var) == ERROR)
		{
			i++;
			continue;
		}
		// supposed to run through all the arguments and set the valid variables
		// break out of the loop if the var name is invalid
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
