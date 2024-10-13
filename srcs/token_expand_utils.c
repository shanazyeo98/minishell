/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/13 09:56:30 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: Checks if a token requires expansion given a token. A token is
   eligible for expansion under the following conditions:
	1. Token contents start with '$' AND
	2. Token type is BASIC or DOUBLE
   Returns a TRUE or FALSE
*/

int	token_expand_eligibiility(t_token *tkn)
{
	if (tkn->str[0] == '$' && (tkn->type == BASIC || tkn->type == DOUBLE))
		return (TRUE);
	else
		return (FALSE);
}

/* Description: Takes in a variable name and the envp linked list. Checks if
   the variable exists within the list and returns the address of the node in
   the linked list. If the variable does not exits, then this function returns
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
		envp_cnt= curr->content;
		if (ft_strncmp(envp_cnt, var, var_len) == 0 && \
		envp_cnt[var_len] == '=')
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

/* Description: takes in an input string and a char. Finds the substring after
   the first instance of the char in the input string. This function should
   only be used when it is confirmed that the char exists within the input
   string. This function is mainly used to
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
	printf("i: %d | len: %ld\n", i, len);
	ret = ft_substr(input, i + 1, len - (i + 1));
	return (ret);
}


/* Description: Takes in a token and scans through the content for parameters
   denoted by $ at the start and delimited by 
*/



// int	main(void)
// {
// 	char	*test;

// 	test = substring_after_char("USER=this is a test", '=');
// 	printf("Check result: %s\n", test);
// }



