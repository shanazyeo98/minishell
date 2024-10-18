/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:19:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/18 15:33:44 by shayeo           ###   ########.fr       */
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

int	gotohome(t_minishell *params)
{
	char	*home;

	home = getenv("HOME"); //to change to own retrieval function
	if (home == NULL)
	{
		ft_putstr_fd(ERR, 2);
		ft_putendl_fd(": cd: HOME not set", 2);
		return (ERROR);
	}
	return (changedir(NULL, home, params, TRUE));
}

int	gotodir(char *dir, t_minishell *params)
{
	if (ft_strcmp(dir, "") == 0)
		return (SUCCESS);
	if (dir[0] == '/')
	{
		if (chdir(dir) == -1)
		{
			cderrormsg(dir);
			perror("");
			return (ERROR);
		}
		return (SUCCESS);
	}
	else
		return (gotorelative(dir, params));
}

int	cd(char **args, t_minishell *params)//, char **env)
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
		status = gotohome(params);
	else
		status = gotodir(args[1], params);
	return (status);
}

int	main(void)
{
	char	*test[4] = {"cd", "42core", "hi", NULL};
	t_minishell	params;

	params.cwd = getcwd(NULL, 0);
	cd(test, &params);
	printf("new cwd: %s\n", params.cwd);
}
