/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:23:51 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/04 04:31:07 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Expands the tokens in the node for variable expansion
and wildcard expansion. Program will exit if malloc fails*/

void	expandtokens(t_cmdnode *node, t_minishell *params)
{
	t_token	*t;

	t = node->start;
	while (t != node->end)
	{
		if (t->type != SINGLE)
		{
			if (token_parameter_expansion(t, params->envp, \
			params->exitstatus) == FAIL)
				spick_and_span(params, FAIL, TRUE);
		}
		t = t->next;
	}
	t = node->start;
	while (t != node->end)
	{
		if (t->type == BASIC && searchstar(t->str, 0) > -1)
		{
			if (wildcard_expansion(t->wordgrp, params) == FAIL)
				spick_and_span(params, FAIL, TRUE);
			while (t->next != NULL && (t->next)->wordgrp != t->wordgrp)
				t = t->next;
		}
		t = t->next;
	}
}

/*Description: Function to execute builtins that do not require a child process
It will open and close the redirectors if applicable.*/

int	nonchildexe(t_cmd *cmd, t_minishell *params)
{
	int	status;
	int	func;

	status = exe_redirection(cmd->redir, params);
	closeredirfds(cmd->redir);
	if (status != SUCCESS)
		return (status);
	func = builtin(cmd->args[0]);
	return (exebuiltin(func, cmd->args, params));
}

/*Description: Function to generate the child processes for applicable
commands. If there is more than one command, pipes will be created.*/

int	forkchild(int count, t_list *cmd, t_minishell *params)
{
	int	status;

	while (cmd != NULL)
	{
		if (exe_redirection(((t_cmd *)cmd->content)->redir, params) == FAIL)
			return (FAIL);

		printf("here\n");
		printcmdlist(cmd);
		printf("index of last in: %d | index of last out: %d\n", get_last_redirector(INPUT, ((t_cmd *)cmd->content)->redir), \
		get_last_redirector(OUTPUT, ((t_cmd *)cmd->content)->redir));

		if (params->exe_index % 2 == 0 && params->exe_index != count - 1)
			status = pipe(params->fd1);
		else if (params->exe_index % 2 == 1 && params->exe_index != count - 1)
			status = pipe(params->fd2);
		if (status == FAIL)
			return (FAIL);
		params->pid[params->exe_index] = fork();
		if (params->pid[params->exe_index] == -1)
			return (free(params->pid), perror(ERR), FAIL);

		// 	function to execute child process;
		if (params->pid[params->exe_index] == 0)
		{
			exe_chd(params, cmd);
		}



		if (params->exe_index % 2 == 1)
			closepipe(params->fd1);
		if (params->exe_index > 0 && params->exe_index % 2 == 0)
			closepipe(params->fd2);
		params->exe_index++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/*Description: Function for the parent process to wait for the child and
retrieves the status.*/

int	waitforchild(int count, t_minishell *params)
{
	int	pid;
	int	status;
	int	final_status;

	pid = 0;
	while (pid != 1)
	{
		pid = wait(&status);
		if (pid == params->pid[count - 1])
		{
			if (WIFEXITED(status))
				final_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				final_status = WTERMSIG(status) + FATALSIGNAL;
		}
	}
	free(params->pid);
	return (final_status);
}

/*Description: Overall function to execute. Following steps will happen:
1. Variable and wildcard expansion
2. Convert tokens into list of arguments and redirections
3. Execution - either in parent or a child process
Returns the exit status of the execution*/

int	execute(t_cmdnode *node, t_minishell *params)
{
	t_cmd	*cmd;
	int		count;

	// int			i;

	expandtokens(node, params);
	updatetree(node, params);
	if (populate_env_and_paths(params) == FAIL)
		return (FAIL);

	//remember to clear the envp_arr and paths at the end of execute

	// printcmdlist(node->cmds);


	// printf("========Check envp string arr========\n");


	// params->envp_arr = llist_to_stray(params->envp);
	// if (params->envp_arr == NULL)
	// 	return (FAIL);

	// i = 0;
	// while (params->envp_arr[i] != NULL)
	// {
	// 	printf("envp stray: %s\n", params->envp_arr[i]);
	// 	i++;
	// }

	// printf("========Check things in path========\n");

	// i = 0;
	// while (params->paths[i] != NULL)
	// {
	// 	printf("path: %s\n", params->paths[i]);
	// 	i++;
	// }

	// return (1);

	count = ft_lstsize(node->cmds);
	cmd = (t_cmd *) node->cmds->content;
	if ((count == 1 && cmd->args != NULL) && builtin(cmd->args[0]) > 6)
		return (nonchildexe(cmd, params));
	else
	{
		params->exe_index = 0;
		params->pid = malloc(sizeof(int) * count);
		if (params->pid == NULL)
			return (FAIL);
		if (forkchild(count, node->cmds, params) == FAIL)
			return (FAIL);
		return (waitforchild(count, params));
	}
}
