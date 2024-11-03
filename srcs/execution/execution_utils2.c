/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:18:20 by mintan            #+#    #+#             */
/*   Updated: 2024/11/03 13:48:47 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: Retrieves the environment path stored in the $PATH variable in
   the envp linked list.
   Returns:
	- success: stores an array of strings containing the different directories if
	           there is something set in the $PATH in params.paths. Otherwise,
			   store a NULL in params.paths
	- failure: returns FAIL
*/

int	getpaths(t_minishell *params)
{
	char	*path;
	int		status;

	status = SUCCESS;
	path = retrieve_env_var("PATH", params->envp, &status);
	if (status == FAIL)
		return (FAIL);
	if (path != NULL)
	{
		params->paths = ft_split(path, ':');
		free (path);
		if (params->paths == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

/* Description: Populates the envp_arr and paths members in the minishell
   structure.
   Returns:
	- success: if params are successfully populated
	- fail: if malloc errors are encountered
*/

int	populate_env_and_paths(t_minishell *params)
{
	params->envp_arr = llist_to_stray(params->envp);
	if (params->envp_arr == NULL)
		return (FAIL);
	return (getpaths(params));
}
