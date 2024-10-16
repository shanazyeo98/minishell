/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_relative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:30:22 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/16 10:39:20 by shayeo           ###   ########.fr       */
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

int	gotorelative(char *dir)
{
	char	**cdpath;
	int		checkwd;
	int		status_cdpath;

	checkwd = FALSE;
	status_cdpath = retcdpath(&cdpath, &checkwd);
	if (status_cdpath == FAIL)
		return (FAIL);
	if (status_cdpath == SUCCESS && checkwd == FALSE)
	{
		//check the cdpath directories first
	}
}
