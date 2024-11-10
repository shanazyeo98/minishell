/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:56:18 by mintan            #+#    #+#             */
/*   Updated: 2024/11/10 11:16:55 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void	spick_and_span(t_minishell *ms, int status, int end)
{
	free(ms->input);
	ms->input = NULL;
	if (ms->envp != NULL && end == TRUE)
	{
		ft_lstclear(&(ms->envp), &free);
		ms->envp = NULL;
	}
	if (ms->tokenlist != NULL)
		freetokens(ms->tokenlist);
	ms->tokenlist = NULL;
	if (ms->ast != NULL)
		free_tree(ms->ast);
	ms->ast = NULL;
	if (status == FAIL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		exit(FAIL);
	}
}
