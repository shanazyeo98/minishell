/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:06:01 by mintan            #+#    #+#             */
/*   Updated: 2024/11/19 18:06:45 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: prints out all the items stored within the envp linked list
   except for the variables with no values. This function only accepts an
   array of strings with 1 string (env) and the envp linked list. If there
   are multiple strings within the array of strings, the function returns an
   ERROR.
*/

int	builtin_env(char **arg, t_list **envp)
{
	int		argcount;
	t_list	*curr;

	argcount = countexeargs(arg);
	curr = *envp;
	if (argcount > 1)
	{
		ft_putstr_fd(ERR, STDERR_FILENO);
		ft_putendl_fd(": env: too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	while (curr != NULL)
	{
		if (ft_strchr((char *)curr->content, '=') != NULL)
			ft_putendl_fd((char *)curr->content, STDOUT_FILENO);
		curr = curr->next;
	}
	return (SUCCESS);
}
