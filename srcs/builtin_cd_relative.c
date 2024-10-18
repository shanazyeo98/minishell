/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_relative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:30:22 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/18 08:06:57 by shayeo           ###   ########.fr       */
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

int	execdpath(t_cd cd, char *dir, int checkwd, t_minishell *params)
{
	char		*combine;

	if (checkwd == TRUE && checkdirexists(cd.path) == TRUE)
		return (changedir(dir, cd.path, params, TRUE));
	while (*(cd.cdpath) != NULL)
	{
		combine = genpath(*(cd.cdpath), dir);
		if (combine == NULL)
			return (FAIL);
		if (checkdirexists(combine) == TRUE)
			return (free(cd.path), changedir(dir, combine, params, TRUE));
		else
			free(combine);
		cd.cdpath++;
	}
	return (changedir(dir, cd.path, params, TRUE));
}

int	gotorelative(char *dir, t_minishell *params)
{
	t_cd	cd;
	int		checkwd;
	int		status_cdpath;
	int		status;

	cd.path = genpath(params->cwd, dir);
	if (cd.path == NULL)
		return (FAIL);
	checkwd = FALSE;
	status_cdpath = retcdpath(&cd.cdpath, &checkwd);
	if (status_cdpath == FAIL)
		return (FAIL);
	if (status_cdpath == ERROR)
		return (changedir(dir, cd.path, params, TRUE));
	status = execdpath(cd, dir, checkwd, params);
	return (ft_freearray(cd.cdpath), status);
}
