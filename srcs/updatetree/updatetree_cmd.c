/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:21:02 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/16 21:28:39 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countargs(char *str, t_token *token, t_token *start, t_token *end)
{
	int	i;
	int	j;

	i = ft_countstr(str, ' ');
	j = 0;
	while (str != NULL && str[j] != '\0')
	{
		if (j == 0 && str[j] == ' ')
		{
			if (token != start && token->wordgrp == (token->prev)->wordgrp)
				i++;
		}
		else if (str[j + 1] == '\0' && str[j] == ' ')
		{
			if (token->next != end && (token->next)->type != REDIRECTOR && \
			token->wordgrp == (token->next)->wordgrp)
				i++;
		}
		j++;
	}
	if (str != NULL && token != start && token->wordgrp == (token->prev)->wordgrp)
		i--;
	return (i);
}

void	skipredir(t_token **token, t_token *end)
{
	int		grp;
	t_token	*next;

	*token = (*token)->next;
	grp = (*token)->wordgrp;
	next = (*token)->next;
	while (next != end && next->wordgrp == grp && next->type != REDIRECTOR)
	{
		*token = (*token)->next;
		next = (*token)->next;
	}
}

void	count(int *args, int *redir, t_token *start, t_token *end)
{
	t_token	*token;
	int		grp;

	token = start;
	grp = token->wordgrp;
	while (token != end)
	{
		if ((token == start || (token->str != NULL && !(token->wordgrp == grp \
		&& token->prev->str[0] != '\0'))) && \
		(token->type == SINGLE || token->type == DOUBLE))
			(*args)++;
		grp = token->wordgrp;
		if (token->type == REDIRECTOR)
		{
			(*redir)++;
			skipredir(&token, end);
			if (token == end)
				break ;
		}
		else if (token->type == BASIC)
			*args += countargs(token->str, token, start, end);
		token = token->next;
	}
}

int	initcmd(t_cmd *cmd, t_token *start, t_token *end)
{
	int	args;
	int	redir;

	args = 0;
	redir = 0;
	count(&args, &redir, start, end);
	if (args > 0)
	{
		cmd->args = malloc(sizeof(char *) * (args + 1));
		if (cmd->args == NULL && args > 0)
			return (FAIL);
		initchararray(cmd->args, args + 1);
	}
	if (redir > 0)
	{
		cmd->redir = malloc(sizeof(t_redir *) * (redir + 1));
		if (cmd->redir == NULL)
			return (FAIL);
		initredirarray(cmd->redir, redir + 1);
	}
	if (fill(cmd, start, end, args) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
