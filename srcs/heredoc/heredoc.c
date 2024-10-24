/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:46:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/24 17:42:42 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Checks if the token is valid to start the heredoc process*/

void	heredoccheck(t_token **tokenlist, t_minishell *params)
{
	t_token	*token;
	char	*limiter;
	int		hd;
	int		status;

	token = *tokenlist;
	hd = 0;
	status = SUCCESS;
	while (token != NULL)
	{
		if ((token->prev) != NULL && (token->prev)->type == REDIRECTOR && \
		ft_strcmp("<<", (token->prev)->str) == 0)
		{
			hd++;
			limiter = delim(token, params);
			if (limiter == NULL)
				spick_and_span(params, FAIL, TRUE);
			status = heredoc(hd, token, limiter, params);
			free(limiter);
			if (status != SUCCESS)
				break ;
		}
		token = token->next;
	}
	if (status == FAIL)
		spick_and_span(params, status, TRUE);
	else if (status == FAIL)
		spick_and_span(params, status, FALSE);
}

/*Description: Uses get next line to retrieve the input and write into the fd*/

void	writeheredoc(int fd, char *delim, t_minishell *params)
{
	char	*input;

	while (1)
	{
		input = readline(HEREDOCPROMPT);
		if (g_sig_status == SIGINT)
		{
			free(delim);
			spick_and_span(params, ERROR, TRUE);
			exit(ERROR);
		}
		if (input == NULL || ft_strcmp(input, delim) == 0)
		{
			if (input == NULL)
				write(1, "\n", 1);
			free(input);
			free(delim);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
}

/*Description: Forks the process to initiate retrieval of input for heredoc.
Main process will wait*/

int	executedoc(int fd, char *delim, t_minishell *params)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror(ERR);
		return (FAIL);
	}
	if (pid == 0)
	{
		init_all_sig_handler(INTERACTIVE);
		writeheredoc(fd, delim, params);
		close(fd);
		spick_and_span(params, SUCCESS, TRUE);
		exit(SUCCESS);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (ERROR);
	}
}

/*Description: Overall process for the heredoc.
Returns: SUCCESS if heredoc is completed
FAIL if malloc failed
CANCEL if process was interrupted*/

int	heredoc(int hd, t_token *token, char *delim, t_minishell *params)
{
	int		fd;
	int		status;

	params->hd_expand = TRUE;
	fd = herefile(hd);
	if (fd == -1)
		return (FAIL);
	status = executedoc(fd, delim, params);
	if (status == SUCCESS)
	{
		token->fd = fd;
		token->hd_expand = params->hd_expand;
	}
	else
		close(fd);
	return (status);
}
