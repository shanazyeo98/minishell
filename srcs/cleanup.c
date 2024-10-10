/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:56:18 by mintan            #+#    #+#             */
/*   Updated: 2024/10/11 01:03:38 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Items to free so far
// **paths from get paths
// *input from readline

/* Description: frees memory allocated for members in an array of strings
   generated from ft_split. The array of strings has NULL as the final member.
   Actions:
	1. Frees the memory allocated for each pointer in the string array (up
	   to the NULL member)
	2. Frees the memory allocated for the array
*/

void	free_ft_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

/* Description: Overall clean up function. Frees all allocated memory:
	- t_minishell -> char **paths
	- t_minishell -> char * input
	- t_minishell -> t_list *envp
	- TO ADD ON AFTERWARDS
*/
void	spick_and_span(t_minishell ms)
{
	free (ms.input);
	free_ft_split(ms.path);
	if (ms.envp != NULL)
		ft_lstclear(&(ms.envp), ft_lst_freecntnt);
}
