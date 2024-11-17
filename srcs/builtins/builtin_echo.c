/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:20:13 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/10 17:51:15 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (args[i] != NULL)
	{
		if (i == 1 && ft_strcmp(args[i], "-n") == 0)
		{
			newline = FALSE;
			while (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
				i++;
		}
		else
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			i++;
			if (args[i] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
	}
	if (newline == TRUE)
		ft_putendl_fd("", STDOUT_FILENO);
	return (SUCCESS);
}

//testing
// int	main(void)
// {
// 	char	*array[5] = {"echo", "-n ", "hello", "    hie", NULL};
// 	echo(array);
// }
