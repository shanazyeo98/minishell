/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:44:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/16 05:37:19 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*newstring(char *str, char *addstr)
{
	char	*result;

	result = ft_strjoin(str, addstr);
	free(str);
	if (result == NULL)
		return (NULL);
	return (result);
}

int	ft_assignstr(char *newstr, char **args)
{
	if (*args != NULL)
	{
		*args = newstring(*args, newstr);
		if (*args == NULL)
			return (FAIL);
	}
	else
	{
		*args = ft_strdup(newstr);
		if (*args == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	splitbasic(t_token *token, char **args, int *i, t_cmd *cmd)
{
	char	**split;
	int		j;
	int		k;

	if ((token->str)[0] == ' ' && args[*i] != NULL)
		(*i)++;
	split = ft_split(token->str, ' ');
	if (split == NULL)
		return (FAIL);
	k = 0;
	while (split[k] != NULL)
	{
		if (ft_assignstr(split[k], args + *i) == FAIL)
			return (ft_freearray(split), FAIL);
		k++;
		if (split[k] != NULL)
			(*i)++;
	}
	j = 0;
	while ((token->str)[j + 1] != '\0')
		j++;
	if ((token->str)[j] == ' ' && token->next != cmd->end && \
	token->wordgrp == (token->next)->wordgrp)
		(*i)++;
	return (ft_freearray(split), SUCCESS);
}

int	det_action(t_cmd *cmd, t_token **token, int *i_arg)
{
	if ((*token)->type == REDIRECTOR)
	{
		if (redirection(cmd, token, cmd->redir) == FAIL)
			return (FAIL);
	}
	else if ((*token)->type == BASIC)
	{
		if (splitbasic(*token, cmd->args, i_arg, cmd) == FAIL)
			return (FAIL);
	}
	else if ((*token)->type == SINGLE || (*token)->type == DOUBLE)
	{
		if (ft_assignstr((*token)->str, cmd->args + *i_arg) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	fill(t_cmd *cmd)
{
	int		i_arg;
	t_token	*token;
	int		grp;

	i_arg = 0;
	token = cmd->start;
	grp = token->wordgrp;
	while (token != cmd->end)
	{
		if (det_action(cmd, &token, &i_arg) == FAIL)
			return (FAIL);
		token = token->next;
		if (token != NULL && token->wordgrp != grp)
		{
			if (cmd->args[i_arg] != NULL)
				i_arg++;
			grp = token->wordgrp;
		}
	}
	return (SUCCESS);
}
