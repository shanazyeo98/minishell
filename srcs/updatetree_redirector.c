/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_redirector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:22:38 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/14 02:25:23 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redirection(t_cmd *cmd, t_token **token, t_redir **redir)
{
	static int	i = 0;
	int			grp;
	int			null;

	redir[i] = malloc(sizeof(t_redir));
	if (redir[i] == NULL)
		return (FAIL);
	(redir[i])->id = ret_redirection((*token)->str);
	*token = (*token)->next;
	if ((redir[i])->id == HEREDOC)
		(redir[i])->fd = (*token)->fd;
	grp = (*token)->wordgrp;
	null = 0;
	while ((*token) != cmd->end && (*token)->wordgrp == grp && (*token)->type != REDIRECTOR)
	{
		if ((redir[i])->id != HEREDOC)
		{
			if ((*token)->type == BASIC && countspaces((*token)->str) > 0)
			{
				null = 1;
				if ((redir[i])->file != NULL)
					free((redir[i])->file);
				(redir[i])->file = NULL;
			}
			else if (null == 0)
			{
				if (ft_assignstr((*token)->str, &(redir[i])->file) == FAIL)
					return (FAIL);
			}
		}
		*token = (*token)->next;
	}
	return (SUCCESS);
}
