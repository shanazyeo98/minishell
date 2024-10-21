/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:34:35 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 10:35:38 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **args, t_minishell params)
{
	char	*dir;
	int		status;

	if (countexeargs(args) > 1)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": pwd: invalid arguments", STDERR_FILENO);
		return (INVALIDUSAGE);
	}
	status = SUCCESS;
	dir = retrieve_env_var(PWDVAR, params.envp, &status);
	if (status == FAIL)
		return (FAIL);
	if (dir == NULL)
		dir = params.cwd;
	ft_putendl_fd(dir, STDOUT_FILENO);
	return (SUCCESS);
}

//testing
// int	main(void)
// {
// 	t_minishell params;

// 	params.cwd = "test";
// 	pwd(params);
// }
