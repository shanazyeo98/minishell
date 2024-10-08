/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:41:04 by mintan            #+#    #+#             */
/*   Updated: 2024/10/08 17:28:44 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: handler function when signals are received:
	- SIGINT: sets rl_done = 1 to break out of readline
*/

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		rl_done = 1;
}

/* Description: Sets up the signal handler using sigaction. Declares the
   sigaction structure that contains the following members:
	- sa_handler: points to the signal handler function
	- sa_mask: a set of signals to be blocked during the execution of the
	  handler
   The signal handler is registered using the sigaction()
*/

void	init_signal_handler(int signum)
{
	struct sigaction	action;

	action.sa_handler = &sig_handler;
	sigemptyset(&action.sa_mask);
	//probably need to register more signals here
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_flags = 0;
	if (sigaction(signum, &action, NULL) == -1)
	{
		perror(ERR_SIGACTION_FAIL);
		exit (EXIT_FAILURE);
	}
}

/* Description: Overall function to setup the signal handler to handle
   different types of signals:
   	- SIGINT
	- SIGQUIT
	- XXXXXX ADD LATER
*/

void	init_all_sig_handler(void)
{
	init_signal_handler(SIGINT);
	init_signal_handler(SIGQUIT);
}
