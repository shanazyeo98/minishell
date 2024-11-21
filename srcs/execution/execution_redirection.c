/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:48:48 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/21 22:55:50 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Opens the input file
Returns: ERROR - if file name has a space inside and is unquoted or unable
to open
Else, SUCCESS*/

int	openinput(t_redir *redir)
{
	int	fd;

	if (redir->file == NULL)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		return (ERROR);
	}
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(ERR);
		return (ERROR);
	}
	redir->fd = fd;
	return (SUCCESS);
}

/*Description: Opens the output file (either truncated or append mode)
Returns: ERROR - if file name has a space inside and is unquoted or unable
to open
Else, SUCCESS*/

int	openoutput(t_redir *redir)
{
	int	fd;

	if (redir->file == NULL)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		return (ERROR);
	}
	if (redir->id == OUTPUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(ERR);
		return (ERROR);
	}
	redir->fd = fd;
	return (SUCCESS);
}

/*Description: Intermediary function to call input / output functions*/

int	handlefiles(t_redir *redir)
{
	int	status;

	if (redir->id == INPUT)
		status = openinput(redir);
	else
		status = openoutput(redir);
	return (status);
}

/*Description: Run through the input and output redirections to open the files.
If the last input file is a heredoc, it will undergo the file generation
and expansion for heredoc accordingly.
Returns: ERROR - if there is any issue opening the file (excluding heredoc)
FAIL - malloc issues or unable to generate file for heredoc
Else, SUCCESS*/

int	exe_redirection(t_redir **redir, t_minishell *params, int parent)
{
	int	input_i;
	int	i;

	if (redir == NULL)
		return (SUCCESS);
	i = 0;
	input_i = -1;
	while (redir[i] != NULL)
	{
		if (redir[i]->id != HEREDOC && handlefiles(redir[i]) == ERROR)
			return (ERROR);
		else if (redir[i]->id == HEREDOC || redir[i]->id == INPUT)
			input_i = i;
		i++;
	}
	if (input_i > -1 && redir[input_i]->id == HEREDOC && parent == FALSE)
	{
		if (expandheredoc(redir[input_i], params) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

/*Description: Loops through the redirection list to close the fds*/

void	closeredirfds(t_redir **redir)
{
	int	i;

	if (redir == NULL)
		return ;
	i = 0;
	while (redir[i] != NULL)
	{
		if (redir[i]->fd != -1)
			close(redir[i]->fd);
		redir[i]->fd = -1;
		i++;
	}
}
