/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:47:28 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/30 17:19:57 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Takes the string generated from the heredoc input and
performs variable expansion if hd_expand is true*/

int	inputheredoc(t_redir *redir, int fd, t_minishell *params)
{
	char	*newstr;
	char	*content;

	content = ft_strdup(redir->hd_content);
	if (content == NULL)
		return (FAIL);
	if (redir->hd_expand == TRUE)
	{
		newstr = parameter_expansion(content, params->envp, params->exitstatus);
		if (newstr == NULL)
			return (FAIL);
		ft_putstr_fd(newstr, fd);
		free(newstr);
	}
	else
	{
		ft_putstr_fd(content, fd);
		free(content);
	}
	return (SUCCESS);
}

/*Description: Generates a file to store the heredoc input and putstr into
the generated file
Returns: FAIL - if file cannot be generated or malloc fails
else, SUCCESS*/

int	expandheredoc(t_redir *redir, t_minishell *params)
{
	static int	i = 0;
	int			fd;

	fd = herefile(i);
	if (fd == -1)
		return (FAIL);
	if (inputheredoc(redir, fd, params) == FAIL)
		return (close(fd), FAIL);
	redir->fd = fd;
	return (i++, SUCCESS);
}

// num = ft_itoa(i);
// 	if (num == NULL)
// 		return (FAIL);
// 	name = ft_strjoin(HEREDOCFILE, num);
// 	if (name == NULL)
// 		return (free(num), FAIL);
// 	unlink(name);
// 	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
// 	free (num);
// 	unlink(name);
// 	free(name);
// 	if (fd == -1)
// 	{
// 		perror(ERR);
// 		return (FAIL);
// 	}
