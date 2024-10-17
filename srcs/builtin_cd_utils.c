/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:06:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/17 05:50:10 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkslash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i == 0)
		return (FALSE);
	if (str[i - 1] == '/')
		return (TRUE);
	return (FALSE);
}

char	*genpath(char *currdir, char *relpath)
{
	char	*combine;
	char	*newstr;

	if (checkslash(currdir) == FALSE)
	{
		newstr = ft_strjoin(currdir, "/");
		if (newstr == NULL)
			return (NULL);
		combine = ft_strjoin(newstr, relpath);
		free(newstr);
	}
	else
		combine = ft_strjoin(currdir, relpath);
	if (combine == NULL)
		return (NULL);
	return (combine);
}

int	changedir(char *path, t_minishell *params)
{
	int	status;

	if (chdir(path) == -1)
	{
		status = ERROR;
		perror(ERR);
		free(path);
	}
	else
	{
		status = SUCCESS;
		params->cwd = path;
	}
	return (status);
}

int	checkdirexists(char *path)
{
	struct stat	dirstat;

	if (stat(path, &dirstat) == 0 && S_ISDIR(dirstat.st_mode) != 0)
		return (TRUE);
	return (FALSE);
}

void	cderrormsg(char *dir)
{
	ft_putstr_fd(ERR, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putendl_fd(": No such directory", 2);
}
