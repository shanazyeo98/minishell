/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/15 08:31:20 by mintan           ###   ########.fr       */
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
	printf("i: %d | len: %ld\n", i, len);
	ret = ft_substr(input, i + 1, len - (i + 1));
	return (ret);
}

/* Description: Retrieves the name of a parameter, given the pointer address of
   the first $. Finds the closest delimiter, space, single quote, double quotes
   or $ and returns a substring of the param name:
   E.g. {$param_name}{delimiter}{remaining}
   E.g. {$param_name}\0
*/

char	*retrieve_param_name(char *str)
{
	char	*param_name;
	int		i;
	int		j;

	i = 1;
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i] != DELIMITER[j] && DELIMITER[j] != '\0')
			j++;
		if (DELIMITER[j] == '\0')
			i++;
		else
		{
			param_name = ft_substr(str, 1, i - 1);
			if (param_name == NULL)
				return (NULL);
			return (param_name);
		}
	}
	param_name = ft_substr(str, 1, i - 1);
	if (param_name == NULL)
		return (NULL);
	return (param_name);
}



/* Description: Takes in a token and scans through the content for parameters
   denoted by $ at the start and delimited by a space, double quotes, single
   quotes and a dollar sign. Checks through theReplaces the content inside content
*/

void	token_parameter_expansion(t_token *token, t_list *envp)
{
	char	*par_name;
	char	*par_dollar;
	t_list	*found_node;
	char	*rep;

	while (ft_strchr(token->str, '$') != NULL)
	{
		par_name = retrieve_param_name(token->str);
		if (par_name == NULL)
		{
			//Logic to free all the allocated memory before exiting
		}
		found_node = find_env_var(par_name, envp);
		par_dollar = ft_strjoin("$", par_name);
		free (par_name);
		// need to do malloc check here
		if (found_node == NULL)
			token->str = ft_strreplace(token->str, par_dollar, "", DELIMITER);	//probably need to malloc check here to
		else
		{
			rep = substring_after_char(token->str, '=');
			if (rep == NULL)
			{
				//Logic to free all the allocated memory before exiting //probably need to malloc check here to
			}
			else
			{
				token->str = ft_strreplace(token->str, par_dollar, rep, DELIMITER);
				free (rep);
			}
		}
	}
}



// int	main(void)
// {
// 	char	*test;
// 	char	*input1;
// 	char	*input2;
// 	char	*input3;
// 	char	*input4;
// 	char	*input5;

// 	char	*param_name1;
// 	char	*param_name2;
// 	char	*param_name3;
// 	char	*param_name4;
// 	char	*param_name5;


// 	test = substring_after_char("USER=this is a test", '=');
// 	printf("Check result: %s\n", test);
// 	input1 = ft_strdup("$VAR1 hi");
// 	input2 = ft_strdup("$VAR1'hi'");
// 	input3 = ft_strdup("$VAR1\"hi");
// 	input4 = ft_strdup("$VAR1$VAR2");
// 	input5 = ft_strdup("$VAR1");


// 	param_name1 = retrieve_param_name(input1);
// 	printf("Input: %s | Param name: %s\n", input1, param_name1);
// 	param_name2 = retrieve_param_name(input2);
// 	printf("Input: %s | Param name: %s\n", input2, param_name2);
// 	param_name3 = retrieve_param_name(input3);
// 	printf("Input: %s | Param name: %s\n", input3, param_name3);
// 	param_name4 = retrieve_param_name(input4);
// 	printf("Input: %s | Param name: %s\n", input4, param_name4);
// 	param_name5 = retrieve_param_name(input5);
// 	printf("Input: %s | Param name: %s\n", input5, param_name5);

// }
