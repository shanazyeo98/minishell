/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:19:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/17 05:57:14 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to retrieve HOME, CDPATH, PWD from the envp list. and set PWD to the new one
//test the behaviour in symlinks

int	countcdargs(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int	gotohome(void)
{
	char	*home;

	home = getenv("HOME"); //to change to own retrieval function
	if (home == NULL)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd(": cd: HOME not set", 2);
		return (ERROR);
	}
	if (chdir(home) == -1)
	{
		perror(ERR);
		return (ERROR);
	}
	return (SUCCESS);
}

int	gotodir(char *dir, t_minishell *params)
{
	if (ft_strcmp(dir, "") == 0)
		return (SUCCESS);
	if (dir[0] == '/')
	{
		if (chdir(dir) == -1)
		{
			ft_putstr_fd(ERR, 2);
			ft_putstr_fd(": cd: ", 2);
			perror(dir);
			return (ERROR);
		}
		return (SUCCESS);
	}
	else
		return (gotorelative(dir, params));
}

int	cd(char **args, char **env, t_minishell *params)
{
	int	argcount;
	int	status;

	argcount = countcdargs(args);
	if (argcount > 2)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd(": cd: too many arguments", 2);
		return (1);
	}
	if (argcount == 1)
		status = gotohome();
	else
		status = gotodir(args[1], params);
	return (status);
}

// int	main(void)
// {
// 	char	*test[4] = {"cd", "test", "test", NULL};

// 	cd(test);
// }
