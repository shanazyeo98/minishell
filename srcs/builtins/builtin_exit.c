/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:55:06 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/24 17:43:52 by shayeo           ###   ########.fr       */
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
		if (ft_isalpha(str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exit_error(char *msg)
{
	ft_putstr_fd(ERR, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (ERROR);
}

int	builtin_exit(char **arg, t_minishell *params)
{
	int	argcount;
	int	exitstat;

	ft_putendl_fd(EXITCMDMSG, 1);
	argcount = countexeargs(arg);
	if (argcount > 2)
		return (exit_error(": exit: too many arguments"));
	else if (argcount == 1)
		exitstat = params->exitstatus;
	else
	{
		if (checkifnumeric(arg[1]) == FALSE)
			return (exit_error(": exit: numeric argument required"));
		exitstat = ft_atoi(arg[1]);
		while (exitstat > 255)
			exitstat %= 256;
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
