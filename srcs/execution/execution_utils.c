/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:24:40 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/22 17:19:47 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closepipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	openpipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror(ERR);
		return (FAIL);
	}
	return (SUCCESS);
}

int	builtin(char *str)
{
	if (ft_strcmp(str, EXPORTCMD) == 0)
		return (EXPORT);
	if (ft_strcmp(str, ENVCMD) == 0)
		return (ENV);
	if (ft_strcmp(str, EXITCMD) == 0)
		return (EXIT);
	if (ft_strcmp(str, CDCMD) == 0)
		return (CD);
	if (ft_strcmp(str, UNSETCMD) == 0)
		return (UNSET);
	if (ft_strcmp(str, ECHOCMD) == 0)
		return (ECHO);
	if (ft_strcmp(str, PWDCMD) == 0)
		return (PWD);
	return (-1);
}

int	exebuiltin(int func, char **args, t_minishell *params)
{
	if (func == ECHO)
		return (echo(args));
	if (func == PWD)
		return (pwd(args, *params));
	// if (func == EXPORT)
	// 	//export
	// if (func == ENV)
	// 	//env
	// if (func == UNSET)
	// 	//unset
	if (func == EXIT)
		return (builtin_exit(args, params));
//	if (func == CD)
	return (cd(args, params));
}
