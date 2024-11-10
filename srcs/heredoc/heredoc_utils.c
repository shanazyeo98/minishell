/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:13:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/10 15:08:12 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Retrieves delimiter*/

char	*delim(t_token *token, t_minishell *params)
{
	int		word;
	char	*temp;
	char	*limiter;

	word = token->wordgrp;
	limiter = ft_strdup(token->str);
	if (limiter == NULL)
		return (NULL);
	token = token->next;
	params->hd_expand = TRUE;
	while (token != NULL && token->wordgrp == word && token->type != OPERATOR \
	&& token->type != REDIRECTOR)
	{
		if (token->type == SINGLE || token->type == DOUBLE)
			params->hd_expand = FALSE;
		temp = limiter;
		limiter = ft_strjoin(limiter, token->str);
		if (limiter == NULL)
			return (free(temp), NULL);
		free(temp);
		token = token->next;
	}
	return (limiter);
}

/*Description: Generates the temporary file to store the heredoc content*/

int	herefile(int hd)
{
	char	*num;
	char	*name;
	int		fd;

	num = ft_itoa(hd);
	if (num == NULL)
		return (-1);
	name = ft_strjoin(HEREDOCFILE, num);
	free(num);
	unlink(name);
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(ERR);
	unlink(name);
	free(name);
	return (fd);
}
