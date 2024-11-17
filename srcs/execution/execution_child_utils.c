/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:21:16 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/16 21:43:58 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirectchild(t_minishell *params, t_list *cmd, int count)
{
	if (exe_redirection(((t_cmd *)cmd->content)->redir, params) == ERROR)
	{
		closeredirfds(((t_cmd *)cmd->content)->redir);
		spick_and_span(params, ERROR, TRUE);
		exit (ERROR);
	}
	redirect_pipes_in(params, cmd);
	redirect_pipes_out(params, cmd, count);
	closepipe(params->fd1);
	closepipe(params->fd2);
	closeredirfds(((t_cmd *)cmd->content)->redir);
}

void	printsignals(int status)
{
	if (status == 3)
		ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}
