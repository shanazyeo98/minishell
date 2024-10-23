/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:48:48 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/22 18:14:26 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	openinput(t_redir *redir)
{
	int	fd;

	if (redir->file == NULL)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd("ambiguous redirect", STDERR_FILENO);
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

int	handlefiles(t_redir *redir)
{
	int	status;

	if (redir->id == INPUT)
		status = openinput(redir);
	else
		status = openoutput(redir);
	return (status);
}

int	exe_redirection(t_redir **redir, t_minishell *params)
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
	if (input_i > -1 && redir[input_i]->id == HEREDOC && \
	redir[input_i]->hd_expand == TRUE)
	{
		if (expandheredoc(redir[input_i], params) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

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
