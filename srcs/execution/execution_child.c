/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:43:30 by mintan            #+#    #+#             */
/*   Updated: 2024/11/09 12:08:52 by mintan           ###   ########.fr       */
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

/* Description: XXXXX
	= unused pipes should be closed for all scenarios
*/

void	close_child_pipes(t_minishell *params, int count, int used)
{
	if (used == FALSE)
	{
		if (params->exe_index % 2 == 0)
		{
			close(params->fd1[0]);
			if (params->exe_index > 0)
				close(params->fd2[1]);
		}
		else if (params->exe_index % 2 == 1)
		{
			close(params->fd1[1]);
			if (params->exe_index < count - 1)
				close(params->fd2[0]);
		}
	}
	else
	{
		if (params->exe_index % 2 == 0 && params->exe_index > 0)
			close (params->fd2[0]);
		else if (params->exe_index % 2 == 1)
			close (params->fd1[0]);
	}
}




/* Description: Redirects the input of a command.
   Scenarios:
	- If there are IN redirectors, redirect STDIN_FILENO to those
	- If there are no IN redirectors and the command is not the first command,
	  redirect STDIN_FILENO to the corresponding pipe FD[0]
   Returns:
	- SUCCESS: if pipe does not fail
	- FAIL: if pipe fails
*/

int	redirect_pipes_in(t_minishell * params, t_list *cmd)
{
	int		in_idx;

	in_idx = get_last_redir(INPUT, ((t_cmd *)cmd->content)->redir);
	if (in_idx != -1)
	{

		if (dup2((((t_cmd *)cmd->content)->redir)[in_idx]->fd,\
		STDIN_FILENO) == -1)
			return (FAIL);
	}
	//there's some pipes to be closed here still
	else
	{
		printf("Inside here 1\n");
		if (params->exe_index % 2 == 0 && params->exe_index > 0)
		{
			printf("Inside here 2\n");

			if (dup2(params->fd2[0], STDIN_FILENO) == -1)
				return (closepipe(params->fd2), FAIL);
			closepipe(params->fd2);
		}
		else if (params->exe_index % 2 == 1 && params->exe_index > 0)
		{
			printf("Inside here 3\n");
			if (dup2(params->fd1[0], STDIN_FILENO) == -1)
				return (closepipe(params->fd1), FAIL);
			closepipe (params->fd1);
		}
	}
	return (SUCCESS);
}

/* Description: Redirects the output of a command.
   Scenarios:
	- If there are OUT redirectors, redirect STDOUT_FILENO to those
	- If there are no OUT redirectors and the command is not the last command,
	  redirect STDOUT_FILENO to the corresponding pipe FD[1]
   Returns:
	- SUCCESS: if pipe does not fail
	- FAIL: if pipe fails
*/

int	redirect_pipes_out(t_minishell *params, t_list *cmd, int count)
{
	int	out_idx;

	ft_putendl_fd("in 1", STDERR_FILENO);
	out_idx = get_last_redir(OUTPUT, ((t_cmd *)cmd->content)->redir);
	if (out_idx != -1)
	{
		ft_putendl_fd("in 2", STDERR_FILENO);
		if (dup2((((t_cmd *)cmd->content)->redir)[out_idx]->fd, \
		STDOUT_FILENO) == -1)
			return (FAIL);
	}
	else
	{
		ft_putendl_fd("in 3", STDERR_FILENO);
		if (params->exe_index % 2 == 0 && params->exe_index != count - 1)
		{
			ft_putendl_fd("in 4", STDERR_FILENO);
			if (dup2(params->fd1[1], STDOUT_FILENO) == -1)
				return (closepipe(params->fd1), FAIL);
			closepipe(params->fd1);
		}
		else if (params->exe_index % 2 == 1 && params->exe_index != count - 1)
		{
			ft_putendl_fd("in 5", STDERR_FILENO);
			if (dup2(params->fd2[1], STDOUT_FILENO) == -1)
				return (closepipe(params->fd2), FAIL);
			closepipe(params->fd2);
		}
	}
	return (SUCCESS);
}


/* Description: Within a child process, executes a command using execve. Execve
   takes over the child if it does not fail
   XXXXXXXXX
*/

int	exe_chd(t_minishell *params, t_list *cmd, int count)
{
	char	*path;
	char	**cmd_args;

	// int		i;

	// printf("Inside execute child now\n");

	if (replace_cmd(params, cmd) == FAIL)
		return (FAIL);

	// close_child_pipes(params, count, FALSE);


	path = ((t_cmd *)cmd->content)->args[0];
	cmd_args = ((t_cmd *)cmd->content)->args;

	// printf("Path: %s\n", path);
	// printf("printing envp array now\n");
	// i = 0;
	// while (params->envp_arr[i] != NULL)
	// {
	// 	printf("envp array: %s\n", params->envp_arr[i]);
	// 	i++;
	// }


	if (redirect_pipes_in(params, cmd) == FAIL)
		return (FAIL);
	if (redirect_pipes_out(params, cmd, count) == FAIL)
		return (FAIL);

	// path = ((t_cmd *)cmd->content)->args[0];
	// cmd_args = ((t_cmd *)cmd->content)->args;






	if (execve(path, cmd_args, params->envp_arr) == -1)
	{
		ft_putendl_fd("execve failed if you see this", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
	//replace command path the t_list cmd.args with the full path -> done
	//use exe_redirection to open all the files and store the fds. continue with next steps if Error -> done (at parent level)
	//only stop if FAIL (malloc issues)
	//redirection
		//find the latest in / heredoc in the cmd.redir array -> done
		//find the latest out / append in the cmd.redir array -> done
		//perform redirection of fds within the child -> done
		//close all the unused fds
	//execve
	//if execve fails,
		//check if we still need to use strerror or if execve will already print out the error message
		//call a cleanup function to free
	//use closeredirfds to close all the fds -> might want to do this at the parent level
}




