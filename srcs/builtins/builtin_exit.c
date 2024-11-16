/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:55:06 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/16 14:42:26 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkifnumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	exit_error(char *msg)
{
	ft_putstr_fd(ERR, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

int	builtin_exit(char **arg, t_minishell *params)
{
	int	argcount;
	int	exitstat;

	ft_putendl_fd(EXITCMDMSG, 1);
	argcount = countexeargs(arg);
	if (argcount == 1)
		exitstat = params->exitstatus;
	else
	{
		exitstat = params->exitstatus;
		if (checkifnumeric(arg[1]) == FALSE)
			exit_error(": exit: numeric argument required");
		exitstat = ft_atoi(arg[1]);
		while (exitstat > 255)
			exitstat %= 256;
	}
	if (argcount != 1 && checkifnumeric(arg[1]) == TRUE && argcount > 2)
	{
		exit_error(": exit: too many arguments");
		return (ERROR);
	}
	spick_and_span(params, SUCCESS, TRUE);
	exit(exitstat);
	return (SUCCESS);
}

// int	main(void)
// {
// 	char	*arg[3] = {"exit", "256", NULL};

// 	builtin_exit(arg);
// }
