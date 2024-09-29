/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:13:04 by mintan            #+#    #+#             */
/*   Updated: 2024/09/30 06:52:17 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* Description: Retrieves the environment path stored in the $PATH variable
   Returns:
	- success: an array of strings containing the different directories if
	           there is something set in the $PATH. Otherwise, return a NULL
	- failure: Usually from malloc failures. Frees any allocated memory and
	           exits the programme
*/

char	**getpaths(void)
{
	char	*path_var;
	char	**paths;

	paths = NULL;
	path_var = getenv("PATH");
	if (path_var != NULL)
	{
		paths = ft_split(path_var, ':');
		if (paths == NULL)
		{
			ft_printf("%s\n", ERR_MALLOC_FAIL);
			exit(EXIT_FAILURE);
		}
	}
	return (paths);
}

