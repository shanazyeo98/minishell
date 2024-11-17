/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/11/17 15:20:28 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i] != DELIMITER[j] && DELIMITER[j] != '\0')
			j++;
		if (DELIMITER[j] == '\0')
			i++;
		else
		{
			param_name = ft_substr(str, 0, i);
			if (param_name == NULL)
				return (NULL);
			return (param_name);
		}
	}
	param_name = ft_substr(str, 0, i);
	if (param_name == NULL)
		return (NULL);
	return (param_name);
}

/* Description: replaces the parameter within the input string with the
   parameter value retrieved from the envp list. If the envp list does not
   contain the parameter, the parameter is replaced by "". Also frees the
   memory allocated for the replacement text and the par_dollar strings.
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/

char	*replace_param(char *input, char *par_dollar, char *rep)
{
	char	*out;

	if (rep == NULL)
		out = ft_strreplace_one(input, par_dollar, "", DELIMITER);
	else
	{
		out = ft_strreplace_one(input, par_dollar, rep, DELIMITER);
		free (rep);
	}
	free (par_dollar);
	return (out);
}

/* Description: replaces any $? within the input string with the exit status.
   Does nothing if there are no instances of $? within the input string. Also
   frees the memory allocated to convert the int exit status to a string via
   ft_itoa.
   Return:
    - SUCCESS: if there are no malloc errors
    - FAIL: if there are malloc errors
*/

char	*replace_exit_status(char *input, int exit_status)
{
	char	*rep;
	char	*out;

	rep = ft_itoa(exit_status);
	if (rep == NULL)
		return (NULL);
	out = ft_strreplace_one(input, "?", rep, "");
	free (rep);
	if (out == NULL)
		return (NULL);
	return (out);
}

/* Description: given the first found position of $ within the input string,
   retrieves the parameter name and attempts to find the corresponding
   parameter value within the envp linked list. Performs a replacement of the
   original parameter within the input string afterwards. If there is no
   corresponding parameter in the envp list, the parameter is replaced with
   "".
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/

char	*find_n_replace_param(char *input, t_list *envp, char *found)
{
	char	*par_name;
	char	*rep;
	int		status;
	char	*out;

	par_name = retrieve_param_name(found);
	if (par_name == NULL)
		return (NULL);
	rep = retrieve_env_var(par_name, envp, &status);
	if (status == FAIL)
		return (free(par_name), NULL);
	out = replace_param(input, par_name, rep);
	if (out == NULL)
		return (NULL);
	return (out);
}

/* Description: Takes in a string and scans through the content for parameters
   denoted by $ at the start and delimited by a space, double quotes, single
   quotes and a dollar sign. The parameter can also be a null-terminated word.
   The input string is split into a linked list where each node is individually
   expanded. The final string is the product of performing a string join on all
   the expanded strings in each node of the linked list.
   Allocates new memory for the string with the expanded parameters.
   Return:
	- A string with newly allocated memory with the parameters expanded. Input
	  string is freed
	- NULL. If there are malloc errors. The input string is not freed
*/

char	*parameter_expansion(char *input, t_list *envp, int exit_status)
{
	t_pamex	px;
	t_list	*cur;

	init_pamex(input, &px);
	if (px.error == TRUE)
		return (NULL);
	cur = px.dollar;
	while (cur != NULL)
	{
		if ((cur == px.dollar && px.first == TRUE) || (cur != px.dollar))
		{
			if (expand_node(cur, px.dollar, exit_status, envp) == FAIL)
				return (NULL);
		}
		cur = cur->next;
	}
	return (join_expanded_str(px.dollar));
}

// int	main(void)
// {
// 	t_pamex	px1;
// 	t_pamex	px2;
// 	t_pamex	px3;
// 	t_list	*curr;

// 	printf("here\n");
// 	init_pamex("$123", &px1);
// 	printf("px1. first: %d | last: %d\n", px1.first, px1.last);
// 	init_pamex("123$", &px2);
// 	printf("px2. first: %d | last: %d\n", px2.first, px2.last);
// 	init_pamex("$123$456??$?$789", &px3);
// 	printf("px3. first: %d | last: %d\n", px3.first, px3.last);
// 	curr = px3.dollar;
// 	printf("print px3 linked list\n");
// 	while (curr != NULL)
// 	{
// 		printf("%s\n", (char *)curr->content);
// 		curr = curr->next;
// 	}
// }
