/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:59:27 by mintan            #+#    #+#             */
/*   Updated: 2024/10/26 10:18:05 by mintan           ###   ########.fr       */
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

/* Description: replaces the parameter within the token string with the
   parameter value retrieved from the envp list. If the envp list does not
   contain the parameter, the parameter is replaced by "". Also frees the
   memory allocated for the replacement text and the par_dollar strings.
   Return:
	- SUCCESS: if there are no malloc errors
	- ERROR: if there are malloc errors
*/
int	replace_param(t_token *token, char *par_dollar, char *rep)
{
	if (rep == NULL)
	{
		token->str = ft_strreplace_one(token->str, par_dollar, "", DELIMITER);
		if (token->str == NULL)
			return (free(par_dollar), ERROR);
	}
	else
	{
		token->str = ft_strreplace_one(token->str, par_dollar, rep, DELIMITER);
		if (token->str == NULL)
			return (free(par_dollar), free (rep), ERROR);
		free (par_dollar);
		free (rep);
	}
	return (SUCCESS);
}

/* Description: replaces any $? within the token string with the exit status.
   Does nothing if there are no instances of $? within the token string. Also
   frees the memory allocated to convert the int exit status to a string via
   ft_itoa.
   Return:
    - SUCCESS: if there are no malloc errors
    - ERROR: if there are malloc errors
*/
int replace_exit_status(t_token *token, int exit_status)
{
    char    *rep;

    rep = ft_itoa(exit_status);
    if (rep == NULL)
        return (FAIL);
    token->str = ft_strreplace_one(token->str, "$?", rep, "");
    if (token->str == NULL)
        return (free(rep), FAIL);
    free (rep);
    return (SUCCESS);
}



/* Description: Takes in a token and scans through the content for parameters
   denoted by $ at the start and delimited by a space, double quotes, single
   quotes and a dollar sign. The parameter can also be a null-terminated word.
   Replaces the content inside the token with the expanded content.
   Return:
	- SUCCESS: if there are no malloc errors
	- ERROR: if there are malloc errors
*/

// int	token_parameter_expansion(t_token *token, t_list *envp, int exit_status)
// {
// 	char	*par_name;
// 	char	*par_dollar;
// 	char	*rep;
// 	int		status;

// 	status = SUCCESS;
// 	if (replace_exit_status(token, exit_status) == FAIL)
// 		return (FAIL);
// 	while (ft_strchr(token->str, '$') != NULL)
// 	{
// 		par_name = retrieve_param_name(ft_strchr(token->str, '$'));
// 		if (par_name == NULL)
// 			return (ERROR);
// 		rep = retrieve_env_var(par_name, envp, &status);
// 		if (status == ERROR)
// 			return (free(par_dollar), ERROR);
// 		par_dollar = ft_strjoin("$", par_name);
// 		free (par_name);
// 		if (par_dollar == NULL)
// 			return (ERROR);
// 		if (replace_param(token, par_dollar, rep) == ERROR)
// 			return (ERROR);
// 	}
// 	return (SUCCESS);
// }

int	token_parameter_expansion(t_token *token, t_list *envp, int exit_status)
{
	char	*par_name;
	char	*par_dollar;
	char	*rep;
	char	*found;
	int		status;

	status = SUCCESS;
	found = ft_strchr(token->str, '$');

	while (found != NULL)
	{
		if (found[1] == '?')
		{
			if (replace_exit_status(token, exit_status) == FAIL)
				return (FAIL);
		}
		else
		{
			par_name = retrieve_param_name(found);
			if (par_name == NULL)
				return (ERROR);
			rep = retrieve_env_var(par_name, envp, &status);
			if (status == ERROR)
				return (free(par_dollar), ERROR);
			par_dollar = ft_strjoin("$", par_name);
			free (par_name);
			if (par_dollar == NULL)
				return (ERROR);
			if (replace_param(token, par_dollar, rep) == ERROR)
				return (ERROR);
		}
		found = ft_strchr(token->str, '$');


	}
	return (SUCCESS);
}
