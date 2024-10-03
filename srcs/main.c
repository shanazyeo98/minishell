/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/02 19:37:53 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

volatile sig_atomic_t	prompt_again = 0;

/* Description: prints the exit message, cleans up all allocated memory, and
   exits the minishell programme. Function is used when Ctrl + D or the "exit"
   command is received.
*/
void	break_shell(t_minishell *ms)
{
	ft_printf(EXIT_MSG);
	spick_and_span(*ms);
	exit(EXIT_SUCCESS);
}


void	sig_handler(int signum)
{
	// printf("Caught signal %d\n", signum);
	if (signum == SIGINT)
	{
		prompt_again = 1;
		// rl_done = 1;
	}
}




/* Description: main programme for minishell
*/

int	main(void)
{
	t_minishell	ms;

	struct sigaction	act;
	sigset_t			signal_set;

	act.sa_handler = &sig_handler;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	act.sa_mask = signal_set;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &act, NULL);



	ms = init_ms();
	while (1)			//use a global variable to store the signal for the while loop?
	{


		getinput(&ms);

		if (prompt_again == 1)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			printf("Caught sigint. enter something\n");
			fflush(stdout);

			// rl_redisplay();
			// getinput(&ms);
			prompt_again = 0;
			continue;
		}
		// getinput(&ms);

		if (ms.input == NULL || (ft_strncmp(ms.input, EXIT_CMD, 4) == 0 &&
		ft_strlen(ms.input) == 4))
			break_shell(&ms);

		// init_signals();
	}



	return (EXIT_SUCCESS);




	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct
	//Clean up

}
