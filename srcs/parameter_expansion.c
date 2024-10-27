/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/27 09:27:01 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: Retrieves the name of a parameter, given the pointer address of
   the first $. Finds the closest delimiter, space, single quote, double quotes
   or $ and returns a substring of the param name:
   E.g. {$param_name}{delimiter}{remaining}
   E.g. {$param_name}\0
*/

static char	*retrieve_param_name(char *str)
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

/* Description: replaces the parameter within the input string with the
   parameter value retrieved from the envp list. If the envp list does not
   contain the parameter, the parameter is replaced by "". Also frees the
   memory allocated for the replacement text and the par_dollar strings.
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/
static int	replace_param(char *input, char *par_dollar, char *rep)
{
	if (rep == NULL)
	{
		input = ft_strreplace_one(input, par_dollar, "", DELIMITER);
		if (input == NULL)
			return (free(par_dollar), FAIL);
	}
	else
	{
		input = ft_strreplace_one(input, par_dollar, rep, DELIMITER);
		if (input == NULL)
			return (free(par_dollar), free (rep), FAIL);
		free (par_dollar);
		free (rep);
	}
	return (SUCCESS);
}

/* Description: replaces any $? within the input string with the exit status.
   Does nothing if there are no instances of $? within the input string. Also
   frees the memory allocated to convert the int exit status to a string via
   ft_itoa.
   Return:
    - SUCCESS: if there are no malloc errors
    - FAIL: if there are malloc errors
*/
static int replace_exit_status(char *input, int exit_status)
{
    char    *rep;

    rep = ft_itoa(exit_status);
    if (rep == NULL)
        return (FAIL);
    input = ft_strreplace_one(input, "$?", rep, "");
    if (input == NULL)
        return (free(rep), FAIL);
    free (rep);
    return (SUCCESS);
}

/* Description: given the first found position of $ within the input string,
   retrieves the parameter name and attempts to find the corresponding
   parameter value within the envp linked list. Performs a replacement of the
   original parameter within the input string afterwards. If there is no
   corresponding parameter in the envp list, the parameter is replkaced with
   "".
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/

static int	find_and_replace_param(char *input, t_list *envp, char *found)
{
	char	*par_name;
	char	*par_dollar;
	char	*rep;
	int		status;

	par_name = retrieve_param_name(found);
	if (par_name == NULL)
		return (FAIL);
	rep = retrieve_env_var(par_name, envp, &status);
	if (status == FAIL)
		return (free(par_name), FAIL);
	par_dollar = ft_strjoin("$", par_name);
	free (par_name);
	if (par_dollar == NULL)
		return (FAIL);
	if (replace_param(input, par_dollar, rep) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/* Description: Takes in a string and scans through the content for parameters
   denoted by $ at the start and delimited by a space, double quotes, single
   quotes and a dollar sign. The parameter can also be a null-terminated word.
   Allocates new memory for the string with the expanded parameters.
   Return:
	- SUCCESS: if there are no malloc errors
	- FAIL: if there are malloc errors
*/

int	parameter_expansion(char *input, t_list *envp, int exit_status)
{
	char	*found;

	found = ft_strchr(input, '$');
	while (found != NULL)
	{
		if (found[1] == '?')
		{
			if (replace_exit_status(input, exit_status) == FAIL)
				return (FAIL);
		}
		else
		{
			if(find_and_replace_param(input, envp, found) == FAIL)
				return (FAIL);
		}
		found = ft_strchr(input, '$');
	}
	return (SUCCESS);
}
