/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:20:13 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/19 16:09:16 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkifflag(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (FALSE);
	if (ft_strncmp(str, "-n", 2) != 0)
		return (FALSE);
	i += 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (args[i] != NULL)
	{
		if (i == 1 && checkifflag(args[i]) == TRUE)
		{
			newline = FALSE;
			while (args[i] != NULL && checkifflag(args[i]) == TRUE)
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
