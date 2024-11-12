/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:06:37 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/12 17:15:28 by shayeo           ###   ########.fr       */
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

int	setpwd(t_minishell *params)
{
	char	*args[3];

	args[0] = "export";
	args[1] = ft_strjoin("OLDPWD=", params->cwd);
	args[2] = NULL;
	if (args[1] == NULL)
		return (free(args[1]), FAIL);
	if (builtin_export(args, &params->envp) == FAIL)
		return (free(args[1]), FAIL);
	free(params->cwd);
	free(args[1]);
	params->cwd = getcwd(NULL, 0);
	if (params->cwd == NULL)
		return (FAIL);
	args[0] = "export";
	args[1] = ft_strjoin("PWD=", params->cwd);
	args[2] = NULL;
	if (args[1] == NULL)
		return (FAIL);
	if (builtin_export(args, &params->envp) == FAIL)
		return (free(args[1]), FAIL);
	free(args[1]);
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
		if (rel == TRUE)
		{
			status = checkmatchingpath(dir, path, params->cwd);
			free(path);
		}
		status = setpwd(params);
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
