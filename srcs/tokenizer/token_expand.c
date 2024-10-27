/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/27 17:15:37 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: Takes in a token and scans through the content for parameters
   denoted by $ at the start and delimited by a space, double quotes, single
   quotes and a dollar sign. The parameter can also be a null-terminated word.
   Replaces the content inside the token with the expanded content.
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/

int	token_parameter_expansion(t_token *token, t_list *envp, int exit_status)
{
	char	*temp;
	char	*out;

	temp = token->str;
	out = parameter_expansion(temp, envp, exit_status);
	if (out == NULL)
		return (FAIL);
	token->str = out;
	return (SUCCESS);
}
