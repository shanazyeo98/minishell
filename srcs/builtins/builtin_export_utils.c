/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/26 11:35:12 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/* Description: Given an argument from the array of arguments, retrieve the
   variable name, check if the name is valid. If the name is invalid, return
   ERROR. Otherwise, replace the existing node within the envp list if there
   is an existing node. Otherwise, add the node in.
*/

int	process_arg(char *arg, t_list **envp)
{
	char	*var;
	t_list	*found;
	t_list	*add;

	var = get_var_name(arg, '=');
	if (var == NULL)
		return (FAIL);
	if (check_var(var) == ERROR)
		return (free(var), ERROR);
	found = find_env_var(var, *envp);
	free (var);
	var = NULL;
	if (found != NULL)
		ft_lstrm_node(envp, found);
	var = ft_strdup(arg);
	if (var == NULL)
		return (FAIL);
	add = ft_lstnew(var);
	if (add == NULL)
		return (free (var), FAIL);
	ft_lstadd_back(envp, add);
	return (SUCCESS);
}

/* Description: takes in an array of strings containing the environment
   variables and their corresponding values.
   For each environment variable:
	- Check if the variable name is valid. Continue to the next variable if the
	  name is not valid
	- Search through the envp linked list for a match and remove that node if
	  there is a match. Add the whole string into the envp linked list after.
   Returns (FAIL) if at least 1 variable name is invalid
*/

int	add_var(t_list **envp, char **args)
{
	int		status;
	int		i;
	int		process;

	i = 1;
	status = SUCCESS;
	while (args[i] != NULL)
	{
		process = process_arg(args[i], envp);
		if (process == ERROR)
			status = ERROR;
		else if (process == FAIL)
			return (FAIL);
		i++;
	}
	return (status);
}
