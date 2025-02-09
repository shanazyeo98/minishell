/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_redirector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:22:38 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/21 23:00:53 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ret_redirection(char *str)
{
	if (ft_strcmp(str, HEREDOCOP) == 0)
		return (HEREDOC);
	if (ft_strcmp(str, APPENDOP) == 0)
		return (APPEND);
	if (ft_strcmp(str, INPUTOP) == 0)
		return (INPUT);
	return (OUTPUT);
}

int	assignfilename(t_token *token, t_redir *redir)
{
	char	**arr;
	int		status;

	if (token->type == BASIC)
	{
		arr = split(token->str);
		if (arr == NULL)
			return (FAIL);
		status = ft_assignstr(*arr, &redir->file);
		free(*arr);
		free(arr);
		if (status == FAIL)
			return (FAIL);
	}
	else
	{
		if (ft_assignstr(token->str, &redir->file) == FAIL)
		{
			if (redir->file != NULL)
				free(redir->file);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	initredir(t_redir **redir, t_token **token, int *grp, int *null)
{
	*redir = malloc(sizeof(t_redir));
	if (*redir == NULL)
		return (FAIL);
	(*redir)->id = ret_redirection((*token)->str);
	(*redir)->file = NULL;
	(*redir)->fd = -1;
	*token = (*token)->next;
	if ((*redir)->id == HEREDOC)
	{
		(*redir)->hd_content = (*token)->hd_content;
		(*redir)->hd_expand = (*token)->hd_expand;
	}
	*grp = (*token)->wordgrp;
	*null = 0;
	return (SUCCESS);
}

int	redirection(t_token *end, t_token **token, t_redir **redir, int *i)
{
	int			grp;
	int			null;

	if (initredir(&(redir[*i]), token, &grp, &null) == FAIL)
		return (FAIL);
	while (1)
	{
		if ((redir[*i])->id != HEREDOC && (*token)->type == BASIC \
		&& countstr((*token)->str) > 1)
		{
			null = 1;
			free((redir[*i])->file);
			(redir[*i])->file = NULL;
		}
		if ((redir[*i])->id != HEREDOC && null == 0 \
		&& assignfilename(*token, redir[*i]) == FAIL)
			return (FAIL);
		if ((*token)->next == end || (*token)->next->wordgrp != grp || \
		(*token)->next->type == REDIRECTOR)
			break ;
		*token = (*token)->next;
	}
	(*i)++;
	return (SUCCESS);
}
