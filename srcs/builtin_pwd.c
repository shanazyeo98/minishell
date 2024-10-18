/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:34:35 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/18 08:18:45 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_minishell params)
{
	char	*dir;

	dir = getenv("PWD");
	if (dir == NULL)
		dir = params.cwd;
	ft_putendl_fd(dir, 1);
	return (SUCCESS);
}

//testing
// int	main(void)
// {
// 	t_minishell params;

// 	params.cwd = "test";
// 	pwd(params);
// }
