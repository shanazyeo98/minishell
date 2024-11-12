/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:34:35 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/12 18:05:52 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **args, t_minishell params)
{
	if (countexeargs(args) > 1)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": pwd: invalid arguments", STDERR_FILENO);
		return (INVALIDUSAGE);
	}
	ft_putendl_fd(params.cwd, STDOUT_FILENO);
	return (SUCCESS);
}

//testing
// int	main(void)
// {
// 	t_minishell params;

// 	params.cwd = "test";
// 	pwd(params);
// }
