/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:06:01 by mintan            #+#    #+#             */
/*   Updated: 2024/10/20 16:11:59 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **arg, t_list *envp)
{
	int 	argcount;
	t_list	*curr;

	argcount = countexeargs(arg);
	curr = envp;
	if (argcount > 1)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": env: too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	while (curr != NULL)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
	return (SUCCESS);
}
