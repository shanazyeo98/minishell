/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:13:04 by mintan            #+#    #+#             */
/*   Updated: 2024/10/28 01:54:25 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




//PROBABLY CAN BE USED ON THE PATH IN ENVP LIST LATER
/* Description: Retrieves the environment path stored in the $PATH variable
   Returns:
	- success: an array of strings containing the different directories if
	           there is something set in the $PATH. Otherwise, return a NULL
	- failure: Usually from malloc failures. Frees any allocated memory and
	           exits the programme
*/

// char	**getpaths(void)
// {
// 	char	*path_var;
// 	char	**paths;

// 	paths = NULL;
// 	path_var = getenv("PATH");
// 	if (path_var != NULL)
// 	{
// 		paths = ft_split(path_var, ':');
// 		if (paths == NULL)
// 		{
// 			ft_printf("%s\n", ERR_MALLOC_FAIL);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (paths);
// }

/* Description: empty function that is called periodically when readline is
   waiting for user input.
*/

int	rl_empty_event(void)
{
	return (0);
}

/* Description: Displays a prompt and stores the user input into a string var
   in the t_minishell structure. Also stores whatever the user inputs into
   the history. Sets the variable rl_event_hook to the address of an empty
   function that is called periodically when readline is waiting for user
   input. This helps reset the prompt when a SIGINT is received.
   Returns:
	- string: user input in the ms struct
*/

void	getinput(t_minishell *ms)
{
	char	*input;

	input = readline(PROMPT);
	if (g_sig_status != SIGINT)
		add_history(input);
	ms->input = input;
}

/* Description: Initialises the t_minishell structure.
   Members:
	- casts int arc and char *argv[] as void to "use" them
	- envp: linked list of environment variables
	- paths: an array of strings containing the environment paths
	- input: user input from the command line
	- TO ADD ON AS WE ADD MORE MEMBERS IN THE STRUCT
*/

t_minishell	init_ms(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	ms.envp = stray_to_llist(envp);
	if (ms.envp == NULL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		exit (ERROR);
	}
	ms.input = NULL;
	ms.tokenlist = NULL;
	ms.ast = NULL;
	ms.hd_expand = TRUE;
	ms.cwd = getcwd(NULL, 0);
	ms.exitstatus = 0;
	declarearray(&ms);
	rl_event_hook = rl_empty_event;
	rl_signal_event_hook = rl_empty_event;
	return (ms);
}
