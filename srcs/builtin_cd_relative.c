/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_relative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:30:22 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/17 06:09:30 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	retcdpath(char ***cdpath, int *checkwd)
{
	char	*path;

	path = getenv(CDPATH); //ret cd path; to replace
	if (path == NULL)
		return (ERROR);
	*cdpath = ft_split(path, ':');
	if (*cdpath == NULL)
		return (FAIL);
	if (path[0] == ':')
		*checkwd = TRUE;
	return (SUCCESS);
}

//stat is used to check if it is a directory as it resolves the symbolic link
//symbolic link could be used to point to things other than a directory

int	checkcdpath(char **cdpath, char *dir, char **result)
{
	char		*combine;
	struct stat	dirstat;

	while (*cdpath != NULL)
	{
		combine = genpath(*cdpath, dir);
		if (combine == NULL)
			return (FAIL);
		if (stat(combine, &dirstat) == 0 && S_ISDIR(dirstat.st_mode) != 0)
		{
			*result = combine;
			return (SUCCESS);
		}
		cdpath++;
	}
	return (ERROR);
}

int	checkcwd(char *dir, t_minishell *params, int last)
{
	char *path;

	path = genpath(params->cwd, dir);
	if (path == NULL)
		return (FAIL);
	if (checkdirexists(path) == TRUE)
		return (changedir(path, params));
}

int	gotorelative(char *dir, t_minishell *params)
{
	char	**cdpath;
	int		checkwd;
	int		status_cdpath;
	char	*path;

	checkwd = FALSE;
	status_cdpath = retcdpath(&cdpath, &checkwd);
	if (status_cdpath == FAIL)
		return (FAIL);
	if (status_cdpath == SUCCESS && checkwd == FALSE)
	{
		if (checkcdpath(cdpath, dir, &path) == SUCCESS)
			return (ft_freearray(cdpath), changedir(path, params));
		else
			//check cwd
	}
	path = genpath(params->cwd, dir);
	if (path == NULL)
		return (ft_freearray(cdpath), FAIL);
	if (checkdirexists(path) == TRUE)
		return (ft_freearray(cdpath), changedir(path, params));
	if (status_cdpath == SUCCESS && checkwd == TRUE)
	{
		if (checkcdpath(cdpath, dir, &path) == SUCCESS)
			return (ft_freearray(cdpath), changedir(path, params));
	}
	return (cderrormsg(dir), ft_freearray(cdpath), ERROR);
}
