/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:55:06 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/18 10:52:19 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **arg, t_minishell *params)
{
	int argcount;
	int	exitstat;

	argcount = countexeargs(arg);
	if (argcount > 2)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	else if (argcount == 2)
		exitstat = params->exitstatus;
	else
	{
		exitstat = ft_atoi(arg[1]);
		while (exitstat > 255)
			exitstat %= 256;
	}
	ft_freearray(arg);
	spick_and_span(params, SUCCESS);
	exit(exitstat);
	return (SUCCESS);
}

// int	main(void)
// {
// 	char	*arg[3] = {"exit", "256", NULL};

// 	builtin_exit(arg);
// }
