/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:43:30 by mintan            #+#    #+#             */
/*   Updated: 2024/11/19 17:26:37 by mintan           ###   ########.fr       */
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
	1. For each command, check if the binary file exists. Return the path if
	   it exists
	2. If the binary file does not exist, combine with each path from **paths
	   and check if the combined filepath exists.
	   - If it exists, ft_strdup into the cmd_paths
	   - If there are no found paths, output the error message exit the child
	     process
	3. If any of the malloc fails, free previously allocated memory and
	   return NULL
*/

char	*get_cmd_path(char *cmd, char **paths, t_minishell *params)
{
	char	*cmd_path;
	int		status;

	cmd_path = NULL;
	if (ft_strchr(cmd, '/') != NULL)
		return (path_getpath(cmd, params));
	else
	{
		if (paths == NULL)
			return (cmd);
		cmd_path = combinedpath_check(cmd, paths, &status);
		if (cmd_path == NULL)
			spick_and_span(params, FAIL, TRUE);
		if (status == NOTEXIST)
			exit(combinedpath_cmdnotfound(cmd, params));
		else
			return (cmd_path);
	}
}

/* Description: Replaces the first argument in the argument array of the
   argument array with the full command path if the command is not the full
   path already. E.g. {"ls", "-l" } -> {"/usr/bin/ls", "-l" }
*/
int	replace_cmd(t_minishell *params, char **args)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = args[0];
	cmd_path = get_cmd_path(cmd_name, params->paths, params);
	if (cmd_path == NULL)
		return (FAIL);
	if (cmd_path != cmd_name)
	{
		free (cmd_name);
		args[0] = cmd_path;
	}
	return (SUCCESS);
}

/* Description: Redirects the input of a command. dup2 should not fail here
   as the fds' validity is checked beforehand already
   Scenarios:
	- If there are IN redirectors, redirect STDIN_FILENO to those
	- If there are no IN redirectors and the command is not the first command,
	  redirect STDIN_FILENO to the corresponding pipe FD[0]
*/

void	redirect_pipes_in(t_minishell *params, t_list *cmd)
{
	int		in_idx;
	t_redir	**redir;

	redir = ((t_cmd *)cmd->content)->redir;
	in_idx = get_last_redir(INPUT, redir);
	if (in_idx != -1)
	{
		if (redir[in_idx]->id == HEREDOC)
			pipeheredoc(redir[in_idx], redir, params);
		else
			dup2(redir[in_idx]->fd, STDIN_FILENO);
	}
	else
	{
		if (params->exe_index % 2 == 0 && params->exe_index > 0)
			dup2(params->fd2[0], STDIN_FILENO);
		else if (params->exe_index % 2 == 1)
			dup2(params->fd1[0], STDIN_FILENO);
	}
}

/* Description: Redirects the output of a command. dup2 should not fail here
   as the fds' validity is checked beforehand already
   Scenarios:
	- If there are OUT redirectors, redirect STDOUT_FILENO to those
	- If there are no OUT redirectors and the command is not the last command,
	  redirect STDOUT_FILENO to the corresponding pipe FD[1]
*/

void	redirect_pipes_out(t_minishell *params, t_list *cmd, int count)
{
	int	out_idx;

	out_idx = get_last_redir(OUTPUT, ((t_cmd *)cmd->content)->redir);
	if (out_idx != -1)
		dup2((((t_cmd *)cmd->content)->redir)[out_idx]->fd, STDOUT_FILENO);
	else
	{
		if (params->exe_index % 2 == 0 && params->exe_index != count - 1)
			dup2(params->fd1[1], STDOUT_FILENO);
		else if (params->exe_index % 2 == 1 && params->exe_index != count - 1)
			dup2(params->fd2[1], STDOUT_FILENO);
	}
}

/* Description: Within a child process, perform the following:
	1. Attempt to open all the files associated with the command both in and
	   out files. Exits the child process the moment an error occurs
	2. Redirect all the input fds if there are files to redirect in. Otherwise
	   redirect in from the pipe or stdin
	3. Redirect all the output fds if there are files to redirect out.
	   Otherwise redirect out to the pipe or stdout
	4. Close all the pipes
	5. Close the redirected fds
	6. Search for the command binary to execute. If the command exists but is
	   not executable, the child process exits. If there are malloc issues,
	   exit the child process with FAIL (256)
	7. Execute the command using execve. Execve takes over the child if it does
	   not fail. perror if execve fails. Free memory, and exit with the errorno
*/

int	exe_chd(t_minishell *params, t_list *cmd, int count)
{
	char	**args;
	int		status;

	redirectchild(params, cmd, count);
	args = ((t_cmd *)cmd->content)->args;
	if (args != NULL && builtin(args[0]) != -1)
	{
		status = exebuiltin(builtin(args[0]), args, params);
		spick_and_span(params, SUCCESS, TRUE);
		exit(status);
	}
	if (args != NULL && replace_cmd(params, args) == FAIL)
		spick_and_span(params, FAIL, TRUE);
	if (args != NULL && execve(args[0], args, params->envp_arr) == -1)
	{
		perror(ERR);
		spick_and_span(params, ERROR, TRUE);
		if (errno == 2)
			exit(127);
		exit(126);
	}
	spick_and_span(params, SUCCESS, TRUE);
	exit (SUCCESS);
}
