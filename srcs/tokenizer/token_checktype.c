/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checktype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:48:55 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/01 13:51:29 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//character matching functions

/*Description: To check if a character exists in an array of characters*/
int	checkarray(char *array, char a)
{
	int	i;

	i = 0;
	while (array[i] != '\0')
	{
		if (a == array[i])
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

/*Description: To return the type of character - Connector, Operator,
Redirector, Others*/
int	chartype(char a, t_minishell *params)
{
	if (checkarray(params->connector, a) == SUCCESS)
		return (CONNECTOR);
	if (checkarray(params->operator, a) == SUCCESS)
		return (OPERATION);
	if (checkarray(params->redirector, a) == SUCCESS)
		return (REDIRECTION);
	return (OTHERS);
}

/*Description: Return the type of token - Single, Double, Operator, Redirector,
Basic*/
int	returntype(char a, t_minishell *params)
{
	if (a == '\'')
		return (SINGLE);
	else if (a == '"')
		return (DOUBLE);
	else if (chartype(a, params) == OPERATION)
		return (OPERATOR);
	else if (chartype(a, params) == REDIRECTION)
		return (REDIRECTOR);
	return (BASIC);
}
