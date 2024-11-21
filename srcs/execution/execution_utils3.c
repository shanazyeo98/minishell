/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:18:20 by mintan            #+#    #+#             */
/*   Updated: 2024/11/19 21:01:02 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: error message to be output when a cmd is not found after
   combining the given command with all paths
*/

int	combinedpath_cmdnotfound(char *cmd, t_minishell *params)
{
	ft_putstr_fd(ERRCOLON, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	spick_and_span(params, CMDNOTFOUND, TRUE);
	return (CMDNOTFOUND);
}

/* Description: Initialises the cmd_path and final_path variables to NULL.
   Function is used to reduce lines to pass norminette for the
   combinedpath_check function.
*/

void	init_paths(char	**cmd_path, char **final_path)
{
	*cmd_path = NULL;
	*final_path = NULL;
}

/* Description: Frees the old final path and strdup a new final path.
   Function is used to reduce lines to pass norminette for the
   combinedpath_check function.
*/

void	get_final_path(char **final_path, char *cmd_path)
{
	free(*final_path);
	*final_path = ft_strdup(cmd_path);
}

/* Description: for each path in the list of paths, combine with the the given
   command and check if the combined path can be executed. Returns either the
   executable command path or the final combined path if there are n executable
   paths.
*/

char	*combinedpath_check(char *cmd, char **paths, int *status)
{
	char	*cmd_path;
	char	*final_path;

	init_paths(&cmd_path, &final_path);
	while (*paths != NULL)
	{
		free (cmd_path);
		cmd_path = ft_pathjoin(*paths, cmd);
		if (cmd_path == NULL)
			return (NULL);
		*status = check_path(cmd_path);
		if (*status == EXE)
			return (cmd_path);
		if (*status == ISADIR || *status == NOTEXE)
		{
			get_final_path(&final_path, cmd_path);
			if (final_path == NULL)
				return (NULL);
		}
		paths++;
	}
	free (cmd_path);
	if (final_path == NULL)
		return (cmd);
	return (final_path);
}
