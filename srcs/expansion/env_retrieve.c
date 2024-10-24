/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_retrieve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 02:33:28 by mintan            #+#    #+#             */
/*   Updated: 2024/10/24 15:21:03 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: Takes in a variable name and the envp linked list. Checks if
   the variable exists within the list and returns the address of the node in
   the linked list. If the variable does not exist, then this function returns
   a NULL.
*/

t_list	*find_env_var(char *var, t_list *envp)
{
	size_t	var_len;
	t_list	*curr;
	char	*envp_cnt;

	var_len = ft_strlen(var);
	curr = envp;
	while (curr != NULL)
	{
		envp_cnt = curr->content;
		if (ft_strncmp(envp_cnt, var, var_len) == 0 && \
		envp_cnt[var_len] == '=')
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

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

/* Description: takes in an input string and a char. Finds the substring after
   the first instance of the char in the input string. This function should
   only be used when it is confirmed that the char exists within the input
   string. This function is mainly used to retrieve the parameter value after
   it is determined that the parameter is confirmed to be within the envp list.
*/
char	*substring_after_char(char *input, char delim)
{
	unsigned int	i;
	size_t			len;
	char			*ret;

	i = 0;
	len = ft_strlen(input);
	while (input[i] != delim)
		i++;
	ret = ft_substr(input, i + 1, len - (i + 1));
	return (ret);
}
