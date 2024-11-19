/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:34:35 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/17 19:36:54 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **args, t_minishell params)
{
	(void)args;
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
