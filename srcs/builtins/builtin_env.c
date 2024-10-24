/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:06:01 by mintan            #+#    #+#             */
/*   Updated: 2024/10/24 15:21:20 by shayeo           ###   ########.fr       */
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
	int 	argcount;
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
			printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
	return (SUCCESS);
}
