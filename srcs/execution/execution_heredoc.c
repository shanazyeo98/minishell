/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:47:28 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/30 11:01:02 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	amendheredoc(int newfd, int oldfd, t_minishell *params)
{
	char	*str;
	char	*newstr;

	while (1)
	{
		str = get_next_line(oldfd);
		if (str == NULL)
			break ;
		newstr = parameter_expansion(str, params->envp, params->exitstatus);
		if (newstr == NULL)
			return (FAIL);
		ft_putstr_fd(newstr, newfd);
		free(newstr);
	}
	close(oldfd);
	return (SUCCESS);
}

int	expandheredoc(t_redir *redir, t_minishell *params)
{
	static int	i = 0;
	char		*num;
	int			fd;
	char		*name;

	num = ft_itoa(i);
	if (num == NULL)
		return (FAIL);
	name = ft_strjoin(HEREDOCFINAL, num);
	if (name == NULL)
		return (free(num), FAIL);
	unlink(name);
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	free (num);
	unlink(name);
	free(name);
	if (fd == -1)
	{
		perror(ERR);
		return (FAIL);
	}
	if (amendheredoc(fd, redir->fd, params) == FAIL)
		return (close(fd), FAIL);
	redir->fd = fd;
	return (SUCCESS);
}
