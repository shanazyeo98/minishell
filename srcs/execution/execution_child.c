/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:43:30 by mintan            #+#    #+#             */
/*   Updated: 2024/11/04 05:09:23 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: generates a cmd path based on the full command and the paths
   passed in.
   Inputs:
	1. cmd: name of the command. E.g.: "ls" or "cat" or "grep". Depending on
	   the user input, cmd may also be the full command path.
	   E.g.: "/usr/bin/cat" or "/usr/bin/ls"
	2. an array of paths. E.g.: {"/usr/bin", "usr/sbin", ...}
   Actions:
	1. For each command, combine with each path from **paths and check if the
	   combined filepath is executable.
	   - If executable, ft_strdup into the cmd_paths if execuable
	   - If there are no executable paths, add the command as it is into
	   cmd_paths
	2. If any of the malloc fails, free previously allocated memory and
	   return NULL

*/

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			cmd_path = ft_pathjoin(paths[i], cmd);
			if (cmd_path == NULL)
				return (NULL);
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			i++;
			free (cmd_path);
		}
	}
	// ft_printf("%s: command not found\n", cmd); // should handle this later when you execve and get errnoent
	return (cmd);
}

/* Description: Replaces the first argument in the argument array of the
   argument array with the full command path if the command is not the full
   path already. E.g. {"ls", "-l" } -> {"/usr/bin/ls", "-l" }
*/
int	replace_cmd(t_minishell *params, t_list *cmd)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = ((t_cmd *)cmd->content)->args[0];
	cmd_path = get_cmd_path(cmd_name, params->paths);
	if (cmd_path == NULL)
		return (FAIL);
	if (cmd_path != cmd_name)
	{
		free (cmd_name);
		((t_cmd *)cmd->content)->args[0] = cmd_path;
	}
	return (SUCCESS);
}

/* Description: Perform all the redirections 

*/


/* Description: Within a child process, executes a command using execve. Execve
   takes over the child if it does not fail
   XXXXXXXXX
*/

int	exe_chd(t_minishell *params, t_list *cmd)
{

	if (replace_cmd(params, cmd) == FAIL)
		return (FAIL);





	return (1);






	//replace command path the t_list cmd.args with the full path -> done
	//use exe_redirection to open all the files and store the fds. continue with next steps if Error -> done (at parent level)
	//only stop if FAIL (malloc issues)
	//redirection
		//find the latest in / heredoc in the cmd.redir array -> done
		//find the latest out / append in the cmd.redir array -> done
		//perform redirection of fds within the child
		//close all the unused fds
	//execve
	//if execve fails,
		//check if we still need to use strerror or if execve will already print out the error message
		//call a cleanup function to free






	//use closeredirfds to close all the fds -> might want to do this at the parent level


}




