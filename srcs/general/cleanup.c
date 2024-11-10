/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:56:18 by mintan            #+#    #+#             */
/*   Updated: 2024/11/10 18:08:52 by mintan           ###   ########.fr       */
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

/* Description: Checks if the envp array and the paths members in the
   t_minishell structure are populated (not NULL). If they are populated, free
   the memory allocated to these 2 members and set them to NULL.
*/

void	free_envp_arr_and_paths(t_minishell *ms)
{
	if (ms->envp_arr != NULL)
	{
		ft_freearray(ms->envp_arr);
		ms->envp_arr = NULL;
	}
	if (ms->paths != NULL)
	{
		ft_freearray(ms->paths);
		ms->paths = NULL;
	}
}

/* Description: Overall clean up function. Frees all allocated memory:
	- t_minishell -> char * input
	- t_minishell -> t_list *envp
	- t_minishell -> char **envp_arr
	- t_minishell -> char **paths

	- TO ADD ON AFTERWARDS
*/
void	spick_and_span(t_minishell *ms, int status, int end)
{
	free(ms->input);
	ms->input = NULL;
	if (ms->envp != NULL && end == TRUE)
	{
		ft_lstclear(&(ms->envp), &free);
		ft_lstclear(&(ms->envp), &free);
		ms->envp = NULL;
	}
	freetokens(ms->tokenlist);
	ms->tokenlist = NULL;
	free_tree(ms->ast);
	ms->ast = NULL;
	if (end == TRUE)
		free(ms->cwd);
	closepipe(ms->fd1);
	closepipe(ms->fd2);
	free_envp_arr_and_paths(ms);
	if (status == FAIL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		exit(FAIL);
	}
}
