/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:23:51 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/29 17:00:53 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expandtokens(t_cmdnode *node, t_minishell *params)
{
	t_token	*token;

	token = node->start;
	while (token != node->end)
	{
		if (token->type != SINGLE)
		{
			if (token_parameter_expansion(token, params->envp, params->exitstatus) == FAIL)
				spick_and_span(params, FAIL, TRUE);
		}
		token = token->next;
	}
	token = node->start;
	while (token != node->end)
	{
		if (token->type == BASIC && searchstar(token->str, 0) > -1)
		{
			if (wildcard_expansion(token->wordgrp, params) == FAIL)
				spick_and_span(params, FAIL, TRUE);
			while (token->next != NULL && (token->next)->wordgrp != token->wordgrp)
				token = token->next;
		}
		token = token->next;
	}
//	print_token_list(*params);
}

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

int	forkchild(int count, t_list *cmd, t_minishell *params)
{
	int	status;

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
		// if (params->pid[params->exe_index] == 0)
		// 	function to execute child process;
		if (params->exe_index % 2 == 1)
			closepipe(params->fd1);
		if (params->exe_index > 0 && params->exe_index % 2 == 0)
			closepipe(params->fd2);
		params->exe_index++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

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

int	execute(t_cmdnode *node, t_minishell *params)
{
	t_cmd	*cmd;
	int		count;

	expandtokens(node, params);
	updatetree(node, params);
	count = ft_lstsize(node->cmds);
	cmd = (t_cmd *) node->cmds->content;
	if (count == 1 && cmd->args != NULL)// && builtin(cmd->args[0]) > 3)
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
