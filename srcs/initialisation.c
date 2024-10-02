/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:13:04 by mintan            #+#    #+#             */
/*   Updated: 2024/10/02 12:03:43 by shayeo           ###   ########.fr       */
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


/* Description: Displays a prompt and stores the user input into a string var
   in the t_minishell structure.
   Also stores whatever the user inputs into the history
   Returns:
	- string: user input
*/

void	getinput(t_minishell *ms)
{
	char	*input;

	input = readline("٩(ఠ益ఠ)۶ > ");
	if (input)
	{
		printf("Your input: %s\n", input);
		add_history(input);
	}
	ms->input = input;
}

/* Description: Initialises the t_minishell structure.
   Members:
	- paths: an array of strings containing the environment paths
	- input: user input from the command line
	- TO ADD ON AS WE ADD MORE MEMBERS IN THE STRUCT
*/

t_minishell	init_ms(void)
{
	t_minishell	ms;

	ms.path = getpaths();
	ms.input = NULL;
	ms.tokenlist = NULL;
	declarearray(&ms);
	return (ms);
}
