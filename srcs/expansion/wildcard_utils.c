/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:57:46 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/06 12:58:56 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	createnewstr(char **newstr, char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (i != 0)
		{
			*newstr = newstring(*newstr, " ");
			if (*newstr == NULL)
				return (FAIL);
		}
		if (i == 0)
		{
			free(*newstr);
			*newstr = NULL;
		}
		*newstr = newstring(*newstr, array[i]);
		if (*newstr == NULL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	swapstrings(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}
