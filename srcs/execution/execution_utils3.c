/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:18:20 by mintan            #+#    #+#             */
/*   Updated: 2024/11/17 17:11:01 by mintan           ###   ########.fr       */
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
	spick_and_span(params, CMDNOTFOUND, FALSE);
	return (CMDNOTFOUND);
}

/* Description: for each path in the list of paths, combine with the the given
   command and check if the combined path can be executed. Returns either the
   executable command path or the final combined path if there are n executable
   paths.
*/

char	*combinedpath_check(char *cmd, char **paths, int *status)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_pathjoin(paths[i], cmd);
		if (cmd_path == NULL)
			return (NULL);
		*status = check_path(cmd_path);
		if (*status == EXE)
			return (cmd_path);
		i++;
	}
	return (cmd_path);
}
