/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:19:58 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/11 10:40:23 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//to retrieve HOME, CDPATH, PWD from the envp list. and set PWD to the new one
//test the behaviour in symlinks

void	cderrormsg(char *dir)
{
	ft_putstr_fd(ERR, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
}

int	countexeargs(char **args)
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
	int		status;

	status = SUCCESS;
	home = retrieve_env_var(HOME, params->envp, &status);
	if (status == FAIL)
		return (FAIL);
	if (home == NULL)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": cd: HOME not set", STDERR_FILENO);
		return (ERROR);
	}
	status = changedir(NULL, home, params, FALSE);
	return (free(home), status);
}

int	gotodir(char *dir, t_minishell *params)
{
	if (ft_strcmp(dir, "") == 0)
		return (SUCCESS);
	if (dir[0] == '/')
		return (changedir(dir, dir, params, FALSE));
	else
		return (gotorelative(dir, params));
}

int	cd(char **args, t_minishell *params)
{
	int	argcount;
	int	status;

	argcount = countexeargs(args);
	if (argcount > 2)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": cd: too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	if (argcount == 1)
		status = gotohome(params);
	else
		status = gotodir(args[1], params);
	return (status);
}

// int	main(void)
// {
// 	char	*test[4] = {"cd", "SRCS", NULL};
// 	t_minishell	params;
// //	char	*temp;

// 	params.cwd = getcwd(NULL, 0);
// //	temp = params.cwd;
// 	cd(test, &params);
// 	printf("new cwd: %s\n", params.cwd);
// 	free(params.cwd);
// //	free(temp);
// }
