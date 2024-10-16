/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:20:13 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/16 07:01:01 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (args[i] != NULL)
	{
		if (i == 1 && ft_strcmp(args[i], "-n") == 0)
			newline = FALSE;
		else
			ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (newline == TRUE)
		ft_putendl_fd("", 1);
	return (SUCCESS);
}

//testing
// int	main(void)
// {
// 	char	*array[5] = {"echo", "-n ", "hello", "    hie", NULL};
// 	echo(array);
// }
