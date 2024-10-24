/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:06:01 by mintan            #+#    #+#             */
/*   Updated: 2024/10/24 15:21:33 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: removes environment variables in the envp linked list. Behaves
   in the following manner depending on the input arguments:
	- no arguments following the "unset" command: nothing happens. Return
	SUCCESS
	- variable does not exist within the envp list: nothing happens. Return
	SUCCESS
	- variable exists within the envp list: node containing the variable is
	removed. Return SUCCESS
*/

int	builtin_unset(char **args, t_list **envp)
{
	int 	i;
	t_list	*found;

	if (countexeargs(args) > 1)
	{
		i = 1;
		while (args[i] != NULL)
		{
			found = find_env_var(args[i], *envp);
			if (found != NULL)
				ft_lstrm_node(envp, found);
			i++;
		}
	}
	return (SUCCESS);
}
