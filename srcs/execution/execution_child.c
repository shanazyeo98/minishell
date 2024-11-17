/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:43:30 by mintan            #+#    #+#             */
/*   Updated: 2024/11/17 09:20:22 by mintan           ###   ########.fr       */
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
// {
// 	char	*cmd_path;
// 	int		len;

// 	len = ft_straylen(paths);
// 	if (access(cmd, F_OK) == 0)
// 		return (cmd);
// 	if (paths != NULL)
// 	{
// 		while (len >= 0)
// 		{
// 			cmd_path = ft_pathjoin(paths[len], cmd);
// 			if (cmd_path == NULL)
// 				return (NULL);
// 			if (access(cmd_path, F_OK) == 0)
// 				return (cmd_path);
// 			len--;
// 			free (cmd_path);
// 		}
// 	}
// 	ft_putstr_fd(ERRCOLON, STDERR_FILENO);
// 	ft_putstr_fd(cmd, STDERR_FILENO);
// 	ft_putendl_fd(": command not found", STDERR_FILENO);
// 	spick_and_span(params, CMDNOTFOUND, FALSE);
// 	exit (CMDNOTFOUND);
// }

{
	char	*cmd_path;
	int		status;
	int		finalstat;
	char	*final;
	int		i;

	final = NULL;
	finalstat = check_path(cmd);
	if (finalstat == EXE)
		return (CMD);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_pathjoin(paths[i], cmd);
		if (cmd_path == NULL)
			return (NULL);
		status = check_path(cmd_path);
		if (status == EXE)
			return (cmd_path);
		if (status == ISADIR || status == NOTEXE)
		{
			if (final != NULL)
				free (final);
			final = cmd_path;
			finalstat = status;
		}
		else
			free (cmd_path);
		i++;
	}
	if (final == NULL)
		final = cmd;
	ft_putstr_fd(ERRCOLON, STDERR_FILENO);
	ft_putstr_fd(final, STDERR_FILENO);
	if (finalstat == NOTEXIST)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (finalstat == ISADIR)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	spick_and_span(params, CMDNOTFOUND, FALSE);
	exit (CMDNOTFOUND);
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
	char	**cmd_args;

	if (exe_redirection(((t_cmd *)cmd->content)->redir, params) == ERROR)
	{
		closeredirfds(((t_cmd *)cmd->content)->redir);
		spick_and_span(params, ERROR, FALSE);
		exit (ERROR);
	}
	redirect_pipes_in(params, cmd);
	redirect_pipes_out(params, cmd, count);
	closepipe(params->fd1);
	closepipe(params->fd2);
	closeredirfds(((t_cmd *)cmd->content)->redir);
	cmd_args = ((t_cmd *)cmd->content)->args;
	if (builtin(cmd_args[0]) != -1)
		exit(exebuiltin(builtin(cmd_args[0]), cmd_args, params));
	if (replace_cmd(params, cmd_args) == FAIL)
		exit (FAIL);
	if (execve(cmd_args[0], cmd_args, params->envp_arr) == -1)
	{
		perror(ERR);
		spick_and_span(params, ERROR, FALSE);
		exit(errno);
	}
	exit (SUCCESS);
}
