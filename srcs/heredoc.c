/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:46:07 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/09 19:37:52 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to think: will there be a case where fd = -1

/*Description: Checks if the token is valid to start the heredoc process*/

int	heredoccheck(t_minishell *params)
{
	t_token	*token;

	token = lsttoken(*(params->tokenlist));
	if (token != NULL && token->id > 0 && (token->prev)->type == REDIRECTOR)
	{
		if (ft_strcmp((token->prev)->str, HEREDOCOP) == 0)
		{
			params->hdcount++;
			return (heredoc(params, token));
		}
	}
	return (SUCCESS);
}

/*Description: Uses get next line to retrieve the input and write into the fd*/

void	writeheredoc(int fd, char *delim)
{
	char	*input;
//	char	buffer[1000000];
//	int	bread;

	while (1)
	{
		ft_putstr_fd(HEREDOCPROMPT, 1);
		input = get_next_line(0);
		if (input == NULL || ft_strcmp(input, delim) == 0)
		{
			free(delim);
			break;
		}
		ft_putstr_fd(input, fd);
		free(input);
	}
//	testing to see what is in the file
// 	lseek(fd, 0, SEEK_SET);
// 	bread = read(fd, buffer, 1000000);
// 	printf("%d\n", bread);
// 	fflush(stdout);
// 	printf("%s", buffer);
// 	fflush(stdout);
}

/*Description: Forks the process to initiate retrieval of input for heredoc.
Main process will wait*/

int	executedoc(t_minishell *params, int fd, char *delim)
{
	int	status;

	params->pid = fork();
	if (params->pid == -1)
	{
		perror(ERR);
		return (FAIL);
	}
	if (params->pid == 0)
	{
		writeheredoc(fd, delim);
		//cleanup function
		exit(SUCCESS);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (CANCEL);
	}
}

/*Description: Generates the temporary file to store the heredoc content*/

int herefile(t_minishell *params)
{
	char	*num;
	char	*name;
	int		fd;

	num = ft_itoa(params->hdcount);
	if (num == NULL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		return (-1);
	}
	name = ft_strjoin(HEREDOCFILE, num);
	free(num);
	unlink(name);
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	unlink(name);
	return (fd);
}

/*Description: Overall process for the heredoc.
Returns: SUCCESS if heredoc is completed
FAIL if malloc failed
CANCEL if process was interrupted*/

int	heredoc(t_minishell *params, t_token *token)
{
	int		fd;
	int		status;

	fd = herefile(params);
	if (fd == -1)
		return (FAIL);
	params->delim = ft_strjoin(token->str, "\n");
	if (params->delim == NULL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, 2);
		exit(FAIL);
	}
	status = executedoc(params, fd, params->delim);
	if (status == SUCCESS)
		token->fd = fd;
	else
		close(fd);
	return (status);
}
