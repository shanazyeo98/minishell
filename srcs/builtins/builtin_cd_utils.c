/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:06:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 16:36:21 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	checkmatchingpath(char *dir, char *path, char *cwd)
{
	char	*subpath;

	subpath = ft_substr(path, 0, ft_strlen(path) - ft_strlen(dir) - 1);
	if (subpath == NULL)
		return (FAIL);
	if (ft_strcmp(subpath, cwd) != 0)
		ft_putendl_fd(path, STDOUT_FILENO);
	free(subpath);
	return (SUCCESS);
}

int	changedir(char *dir, char *path, t_minishell *params, int rel)
{
	int	status;

	if (chdir(path) == -1)
	{
		status = ERROR;
		cderrormsg(dir);
		perror("");
		if (rel == TRUE)
			free(path);
	}
	else
	{
		status = SUCCESS;
		if (rel == TRUE && checkmatchingpath(dir, path, params->cwd) == FAIL)
			return (FAIL);
		params->cwd = getcwd(NULL, 0);
		if (rel == TRUE)
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

	if (stat(path, &dirstat) == 0 && S_ISDIR(dirstat.st_mode) != 0)
		return (TRUE);
	return (FALSE);
}
