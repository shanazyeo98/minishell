/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:13:04 by mintan            #+#    #+#             */
/*   Updated: 2024/11/10 16:24:21 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/* Description: Initialises all the fds stored in fd1 and fd2 to -1 */

void	init_fds(t_minishell *ms)
{
	ms->fd1[0] = -1;
	ms->fd1[1] = -1;
	ms->fd2[0] = -1;
	ms->fd2[1] = -1;
}

/* Description: Initialises the t_minishell structure.
   Members:
	- casts int arc and char *argv[] as void to "use" them
	- envp: linked list of environment variables
	- envp_arr: used later during child execution when the envp linked is
	  converted back to an array of strings
	- paths: array of strings storing the different direcotries in the $PATH
	  variable. Used for child execution
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
	if (ms.envp == NULL && *envp != NULL)
	{
		ft_putendl_fd(ERR_MALLOC_FAIL, STDERR_FILENO);
		exit (ERROR);
	}
	ms.envp_arr = NULL;
	ms.paths = NULL;
	ms.input = NULL;
	ms.tokenlist = NULL;
	ms.ast = NULL;
	ms.hd_expand = TRUE;
	ms.cwd = getcwd(NULL, 0);
	ms.exitstatus = 0;
	init_fds(&ms);
	declarearray(&ms);
	rl_event_hook = rl_empty_event;
	rl_signal_event_hook = rl_empty_event;
	return (ms);
}
