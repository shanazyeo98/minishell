/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:18:20 by mintan            #+#    #+#             */
/*   Updated: 2024/11/17 19:14:43 by shayeo           ###   ########.fr       */
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

/* Description: Retrieves the index of the latest in (< / <<) or out (> / >>)
   redirector in the array of redirectors.
   Input:
	- type: in or out. Checks for the different types of redirectors based on
	  the type
   Return:
	- the index of the found redir
	- returns -1 if there are no found redir for the specified type
*/

int	get_last_redir(int type, t_redir **redir)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (redir != NULL && redir[i] != NULL)
	{
		if (type == INPUT && \
		(redir[i]->id == INPUT || redir[i]->id == HEREDOC))
			last = i;
		else if (type == OUTPUT && \
		(redir[i]->id == OUTPUT || redir[i]->id == APPEND))
			last = i;
		i++;
	}
	return (last);
}

/* Description: performs the following checks on a given path:
	- checks if the path exists
	- if it exists, checks if the path is a directory
	- if it is not a directory, checks if the file has execute access
*/

int	check_path(char *path)
{
	struct stat	statbuf;
	int			status;

	status = stat(path, &statbuf);
	if (status != 0)
		return (NOTEXIST);
	if (S_ISDIR(statbuf.st_mode) == TRUE)
		return (ISADIR);
	if (access(path, X_OK) == 0)
		return (EXE);
	return (NOTEXE);
}

/* Description: given a file path, checks the path and returns an error message
   if the given path is a directory. Otherwise, return the given file path as
   it is and let it be handled by execve subsequently
*/

char	*path_getpath(char	*path, t_minishell *params)
{
	int	status;

	status = check_path(path);
	if (status != ISADIR)
		return (path);
	ft_putstr_fd(ERRCOLON, STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": is a directory", STDERR_FILENO);
	spick_and_span(params, NOTEXECUTABLE, TRUE);
	exit (NOTEXECUTABLE);
}
