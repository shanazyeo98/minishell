/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_retrieve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 02:33:28 by mintan            #+#    #+#             */
/*   Updated: 2024/10/17 03:29:17 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: retrieves the value of the of an environment variable given the
   the variable name (without $) and the envp list. Returns a NULL if the given
   variable does not exist within the list. If malloc fails, the status is set
   as ERROR.
*/

char	*retrieve_env_var(char *var, t_list *envp, int *status)
{
	t_list	*found_node;
	char	*value;

	found_node = find_env_var(var, envp);
	if (found_node == NULL)
		return (NULL);
	value = substring_after_char(found_node->content, '=');
	if (value == NULL)
	{
		*status = ERROR;
		return (NULL);
	}
	*status = SUCCESS;
	return (value);
}
