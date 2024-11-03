/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:46:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/03 16:46:21 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Checks if the token is valid to start the heredoc process*/

void	heredoccheck(t_token **tokenlist, t_minishell *params)
{
	t_token	*token;
	char	*limiter;
	int		status;

	token = *tokenlist;
	status = SUCCESS;
	while (token != NULL)
	{
		if ((token->prev) != NULL && (token->prev)->type == REDIRECTOR && \
		ft_strcmp(HEREDOCOP, (token->prev)->str) == 0)
		{
			limiter = delim(token, params);
			if (limiter == NULL)
				spick_and_span(params, FAIL, TRUE);
			status = heredoc(token, limiter, params);
			free(limiter);
			if (status != SUCCESS)
				break ;
		}
		token = token->next;
	}
	if (status == FAIL)
		spick_and_span(params, status, TRUE);
	else if (status == ERROR)
		spick_and_span(params, status, FALSE);
}

/*Description: Stores heredoc input as a string.
Returns ERROR if interrupted by a signal*/

int	writeheredoc(t_token *token, char *delim)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(HEREDOCPROMPT);
		if (g_sig_status == SIGINT)
		{
			free(input);
			return (ERROR);
		}
		if (input == NULL || ft_strcmp(input, delim) == 0)
		{
			free(input);
			break ;
		}
		token->hd_content = newstring(token->hd_content, input);
		token->hd_content = newstring(token->hd_content, "\n");
		free(input);
		if (token->hd_content == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

/*Description: Overall process for the heredoc.
Returns: SUCCESS if heredoc is completed
FAIL if malloc failed
ERROR if process was interrupted*/

int	heredoc(t_token *token, char *delim, t_minishell *params)
{
	int		status;

	status = writeheredoc(token, delim);
	if (status == SUCCESS)
		token->hd_expand = params->hd_expand;
	return (status);
}
