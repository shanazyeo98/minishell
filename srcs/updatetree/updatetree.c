/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:02:29 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/17 20:20:01 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//To comment out
void	printcmdlist(t_list *node)
{
	t_cmd	*cmd;
	int		i;

	while (node != NULL)
	{
		printf("NODE:\n");
		printf("args: \n");
		cmd = (t_cmd *) node->content;
		i = 0;
		while (cmd->args != NULL && cmd->args[i] != NULL)
		{
			printf("%s\n", cmd->args[i]);
			i++;
		}
		printf("redirections: \n");
		i = 0;
		while (cmd->redir != NULL && cmd->redir[i] != NULL)
		{
			printf("file: %s\n", cmd->redir[i]->file);
			printf("fd: %d\n", cmd->redir[i]->fd);
			printf("hd expand: %d\n", cmd->redir[i]->hd_expand);
			printf("id: %d\n", cmd->redir[i]->id);
			printf("heredoc content: %s\n", cmd->redir[i]->hd_content);
			i++;
		}
		node = node->next;
	}
}

void	initchararray(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		array[i] = NULL;
		i++;
	}
}

void	initredirarray(t_redir **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		array[i] = NULL;
		i++;
	}
}

int	createcmdlist(t_token *start, t_token *end, t_cmdnode *cmdnode)
{
	t_cmd	*cmd;
	t_list	*lst;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (FAIL);
	cmd->args = NULL;
	cmd->redir = NULL;
	if (initcmd(cmd, start, end) == FAIL)
		return (FAIL);
	lst = ft_lstnew(cmd);
	ft_lstadd_back(&cmdnode->cmds, lst);
	return (SUCCESS);
}

void	updatetree(t_cmdnode *cmdnode, t_minishell *params)
{
	t_token	*token;
	t_token	*start;

	token = cmdnode->start;
	start = token;
	while (token != cmdnode->end)
	{
		if (token->type == OPERATOR)
		{
			if (createcmdlist(start, token, cmdnode) == FAIL)
				spick_and_span(params, FAIL, TRUE);
			token = token->next;
			start = token;
		}
		else
			token = token->next;
	}
	if (createcmdlist(start, cmdnode->end, cmdnode) == FAIL)
		spick_and_span(params, FAIL, TRUE);
}
