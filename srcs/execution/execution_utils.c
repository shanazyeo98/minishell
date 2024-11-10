/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:24:40 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/10 15:47:41 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Description: Close the fds in a pipe*/

void	closepipe(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	fd[0] = -1;
	fd[1] = -1;
}

/*Description: pipe a fd[2]
Return: FAIL - if pipe fails
Else, SUCCESS*/

int	openpipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror(ERR);
		return (FAIL);
	}
	return (SUCCESS);
}

/*Description: Determine if the command belongs to any builtin
Returns -1 if unable to match*/

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
	if (ft_strcmp(str, POSITIVECMD) == 0)
		return (POSITIVE);
	if (ft_strcmp(str, FLIRTCMD) == 0)
		return (FLIRT);
	if (ft_strcmp(str, DUCKCMD) == 0 || ft_strcmp(str, CONDUCKCMD) == 0)
		return (DUCK);
	if (ft_strcmp(str, SOPHDUCKCMD) == 0)
		return (SOPHDUCK);
	if (ft_strcmp(str, DEPRESSCMD) == 0)
		return (DEPRESS);
	return (-1);
}

/*Description: Executes the builtin*/

int	exebuiltin(int func, char **args, t_minishell *params)
{
	if (func == ECHO)
		return (echo(args));
	if (func == PWD)
		return (pwd(args, *params));
	if (func == EXPORT)
		return (builtin_export(args, &params->envp));
	if (func == ENV)
		return (builtin_env(args, &params->envp));
	if (func == UNSET)
		return (builtin_unset(args, &params->envp));
	if (func == EXIT)
		return (builtin_exit(args, params));
	if (func == CD)
		return (cd(args, params));
	if (func == POSITIVE)
		return (positivemsg());
	if (func == DUCK)
		return (duck(args));
	if (func == SOPHDUCK)
		return (sophduck());
	if (func == DEPRESS)
		return (depressedmsg());
	return (flirtmsg());
}
