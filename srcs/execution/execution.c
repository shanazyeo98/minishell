/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:23:51 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/16 13:52:57 by shayeo           ###   ########.fr       */
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
			if (token_expansion(t, params->envp, \
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
			while (t->next != NULL && (t->next)->wordgrp == t->wordgrp)
				t = t->next;
		}
		t = t->next;
	}
}

/*Description: Function to execute builtins that do not require a child process
It will open and close the redirectors if applicable.*/

int	nonchildexe(t_list *cmdlist, t_minishell *params)
{
	int		status;
	int		func;
	int		original;
	t_cmd	*cmd;

	cmd = (t_cmd *) cmdlist->content;
	params->exe_index = 0;
	status = exe_redirection(cmd->redir, params);
	if (builtin(cmd->args[0]) != EXIT)
	{
		original = dup(STDOUT_FILENO);
		redirect_pipes_out(params, cmdlist, 1);
	}
	closeredirfds(cmd->redir);
	if (status != SUCCESS)
		return (status);
	func = builtin(cmd->args[0]);
	status = exebuiltin(func, cmd->args, params);
	if (builtin(cmd->args[0]) != EXIT)
	{
		dup2(original, STDOUT_FILENO);
		close(original);
	}
	return (status);
}

/*Description: Function to generate the child processes for applicable
commands. If there is more than one command, pipes will be created.*/

int	forkchild(int count, t_list *cmd, t_minishell *params)
{
	int	status;

	status = SUCCESS;
	while (cmd != NULL)
	{
		if (params->exe_index % 2 == 0 && params->exe_index != count - 1)
			status = pipe(params->fd1);
		else if (params->exe_index % 2 == 1 && params->exe_index != count - 1)
			status = pipe(params->fd2);
		if (status == FAIL)
			return (FAIL);
		params->pid[params->exe_index] = fork();
		if (params->pid[params->exe_index] == -1)
			return (free(params->pid), perror(ERR), FAIL);
		if (params->pid[params->exe_index] == 0)
			exe_chd(params, cmd, count);
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
	int	fail;
	int	newline;

	pid = 0;
	fail = FALSE;
	newline = FALSE;
	while (pid != -1)
	{
		pid = wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == FAIL)
			fail = TRUE;
		if (WIFSIGNALED(status) && WTERMSIG(status) != 13)
			newline = TRUE;
		if (pid == params->pid[count - 1] && WIFEXITED(status))
			params->exitstatus = WEXITSTATUS(status);
		if (pid == params->pid[count - 1] && WIFSIGNALED(status))
			params->exitstatus = WTERMSIG(status) + FATALSIGNAL;
	}
	if (fail == TRUE)
		return (FAIL);
	if (newline == TRUE)
		write(1, "\n", 1);
	return (SUCCESS);
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

	expandtokens(node, params);
	updatetree(node, params);
	if (populate_env_and_paths(params) == FAIL)
		return (FAIL);
	count = ft_lstsize(node->cmds);
	cmd = (t_cmd *) node->cmds->content;
	if ((count == 1 && cmd->args != NULL) && builtin(cmd->args[0]) > 7)
		return (nonchildexe(node->cmds, params));
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
	ft_freearray(params->envp_arr);
	free (params->paths);
}
