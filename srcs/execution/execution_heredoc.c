/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:47:28 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/14 16:55:21 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Generates a file to store the heredoc input and putstr into
the generated file
Returns: FAIL - if file cannot be generated or malloc fails
else, SUCCESS*/

int	expandheredoc(t_redir *redir, t_minishell *params)
{
	if (redir->hd_expand == TRUE && redir->hd_content != NULL)
	{
		redir->hd_content = parameter_expansion(redir->hd_content, \
		params->envp, params->exitstatus);
		if (redir->hd_content == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

void	pipeheredoc(t_redir *redir, t_redir **list, t_minishell *params)
{
	int	hd[2];

	if (pipe(hd) == -1)
	{
		closeredirfds(list);
		spick_and_span(params, FAIL, TRUE);
	}
	ft_putstr_fd(redir->hd_content, hd[1]);
	dup2(hd[0], STDIN_FILENO);
	closepipe(hd);
}
