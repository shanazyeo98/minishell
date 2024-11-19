/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:44:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/19 15:38:23 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*newstring(char *str, char *addstr)
{
	char	*result;

	result = ft_strjoin(str, addstr);
	if (str != NULL)
		free(str);
	if (result == NULL)
		return (NULL);
	return (result);
}

int	ft_assignstr(char *newstr, char **args)
{
	if (args == NULL)
		return (SUCCESS);
	if (*args != NULL)
		*args = newstring(*args, newstr);
	else
		*args = ft_strdup(newstr);
	if (*args == NULL)
		return (FAIL);
	return (SUCCESS);
}

int	splitbasic(t_token *token, char **args, int *i, t_token *end)
{
	char	**arr;
	int		j;
	int		k;

	if (ft_isspace((token->str)[0]) == 1 && args[*i] != NULL)
		(*i)++;
	arr = split(token->str);
	if (arr == NULL)
		return (FAIL);
	k = 0;
	while (arr[k] != NULL)
	{
		if (ft_assignstr(arr[k], args + *i) == FAIL)
			return (ft_freearray(arr), FAIL);
		k++;
		if (arr[k] != NULL)
			(*i)++;
	}
	j = 0;
	while ((token->str)[j] != '\0' && (token->str)[j + 1] != '\0')
		j++;
	if (ft_isspace((token->str)[j]) == 1 && token->next != end && \
	token->wordgrp == (token->next)->wordgrp && j != 0)
		(*i)++;
	return (ft_freearray(arr), SUCCESS);
}

int	det_action(t_cmd *cmd, t_token **token, int *i_arg, t_token *end)
{
	if ((*token)->type == BASIC && (*token)->str != NULL)
	{
		if (splitbasic(*token, cmd->args, i_arg, end) == FAIL)
			return (FAIL);
	}
	else if ((*token)->type == SINGLE || (*token)->type == DOUBLE)
	{
		if (ft_assignstr((*token)->str, cmd->args + *i_arg) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	fill(t_cmd *cmd, t_token *start, t_token *end, int args)
{
	int		i_arg;
	int		i_redir;
	int		grp;

	i_arg = 0;
	i_redir = 0;
	grp = start->wordgrp;
	while (start != end)
	{
		if (args != 0 && det_action(cmd, &start, &i_arg, end) == FAIL)
			return (FAIL);
		if (start->type == REDIRECTOR)
		{
			if (redirection(end, &start, cmd->redir, &i_redir) == FAIL)
				return (FAIL);
		}
		start = start->next;
		if (start != NULL && start->wordgrp != grp)
		{
			if (cmd->args != NULL && cmd->args[i_arg] != NULL)
				i_arg++;
			grp = start->wordgrp;
		}
	}
	return (SUCCESS);
}
