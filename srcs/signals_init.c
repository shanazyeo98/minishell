/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:41:04 by mintan            #+#    #+#             */
/*   Updated: 2024/10/10 16:33:24 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: handler function when signals are received:
	- SIGINT: sets rl_done = 1 to break out of readline
*/

void	sig_child(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(CANCEL);
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		rl_done = 1;
}

void	sig_noninteractive(int signum)
{
	if (signum == SIGINT)
		return ;
//	if (signum == SIGINT)
//		kill(0, SIGINT);
}

/* Description: Sets up the signal handler using sigaction. Declares the
   sigaction structure that contains the following members:
	- sa_handler: points to the signal handler function
	- sa_mask: a set of signals to be blocked during the execution of the
	  handler
   The signal handler is registered using the sigaction()
*/

void	init_signal_handler(int signum, void (*func)(int))
{
	struct sigaction	action;

	action.sa_handler = func;
	sigemptyset(&action.sa_mask);
	//probably need to register more signals here
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_flags = SA_RESTART;
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

void	init_all_sig_handler(int state)
{
	if (state == INTERACTIVE)
	{
		init_signal_handler(SIGINT, &sig_handler);
		init_signal_handler(SIGQUIT, &sig_handler);
	}
	else
	{
		init_signal_handler(SIGINT, &sig_noninteractive);
		init_signal_handler(SIGQUIT, &sig_noninteractive);
	}
}
