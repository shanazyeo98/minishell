/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:52:19 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/29 16:49:49 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*nonwccheck(char *file, char *oldpos, t_list *wclist, int i)
{
	char	*str;
	char	*pos;

	str = (char *) wclist->content;
	pos = ft_strnstr(file, str, ft_strlen(file));
	if (pos == NULL)
		return (NULL);
	if ((i == 0 && pos != file) || (oldpos != NULL && pos < oldpos))
		return (NULL);
	if (wclist->next == NULL && ft_strlen(str) != ft_strlen(pos))
		return (NULL);
	return (pos);
}

int	patternmatch(char *file, t_list *wclist)
{
	int		i;
	char	*oldpos;

	i = 0;
	oldpos = NULL;
	while (wclist != NULL)
	{
		if (wclist->content != NULL)
		{
			oldpos = nonwccheck(file, oldpos, wclist, i);
			if (oldpos == NULL)
				return (FALSE);
		}
		if (i == 0 && wclist->content == NULL && file[0] == '.')
			return (FALSE);
		i++;
		wclist = wclist->next;
	}
	return (TRUE);
}

int	checkfile(char *file, t_list *wclist, char **str)
{
	if (patternmatch(file, wclist) == TRUE)
	{
		if (*str == NULL)
		{
			*str = ft_strdup(file);
			if (*str == NULL)
				return (FAIL);
		}
		else
		{
			*str = newstring(*str, " ");
			if (*str == NULL)
				return (FAIL);
			*str = newstring(*str, file);
			if (*str == NULL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	searchdir(char **newstr, t_list *wclist, char *cwd)
{
	DIR				*dirstream;
	struct dirent	*direntry;

	*newstr = NULL;
	dirstream = opendir(cwd);
	if (dirstream == NULL)
		return (ERROR);
	while (1)
	{
		direntry = readdir(dirstream);
		if (direntry == NULL)
			break ;
		if (ft_strcmp(direntry->d_name, ".") != 0 && \
		ft_strcmp(direntry->d_name, "..") && \
		checkfile(direntry->d_name, wclist, newstr) == FAIL)
			return (closedir(dirstream), FAIL);
	}
	closedir(dirstream);
	if (*newstr == NULL)
		return (ERROR);
	return (SUCCESS);
}
