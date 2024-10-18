/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:06:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/18 15:33:11 by shayeo           ###   ########.fr       */
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

void	checkmatchingpath(char *path, char *cwd)
{
	int		i;
	int		a;
	char	*subpath;

	i = ft_strlen(path);
	a = i;
	while (i >= 0)
	{
		if (i != a && path[i] == '/')
			break;
		i--;
	}
	subpath = ft_substr(path, 0, i);
	if (ft_strcmp(subpath, cwd) != 0)
		ft_putendl_fd(path, 1);
	free(subpath);
}

int	changedir(char *dir, char *path, t_minishell *params, int clear)
{
	int	status;

	if (chdir(path) == -1)
	{
		status = ERROR;
		cderrormsg(dir);
		perror("");
		if (clear == TRUE)
			free(path);
	}
	else
	{
		status = SUCCESS;
		if (clear == FALSE)
			checkmatchingpath(path, params->cwd);
		params->cwd = ft_strdup(path);
		if (clear == TRUE)
			free(path);
		if (params->cwd == NULL)
			return (FAIL);
		//set pwd variable
	}
	return (status);
}

int	checkdirexists(char *path)
{
	struct stat	dirstat;

	stat(path, &dirstat);
	if (S_ISDIR(dirstat.st_mode) != 0)
		return (TRUE);
	return (FALSE);
}

void	cderrormsg(char *dir)
{
	ft_putstr_fd(ERR, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
}
