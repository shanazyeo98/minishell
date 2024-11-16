/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:41:04 by mintan            #+#    #+#             */
/*   Updated: 2024/11/16 15:17:31 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: handler function when signals are received:
	- SIGINT: sets rl_done = 1 to break out of readline
*/

int	g_sig_status = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		g_sig_status = SIGINT;
	}
}

void	sig_noninteractive(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		g_sig_status = signum;
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
	sigaddset(&action.sa_mask, signum);
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
*/

void	init_all_sig_handler(int state)
{
	if (state == INTERACTIVE)
	{
		init_signal_handler(SIGINT, &sig_handler);
		init_signal_handler(SIGQUIT, SIG_IGN);
	}
	else if (state == CHILD)
	{
		init_signal_handler(SIGINT, SIG_DFL);
		init_signal_handler(SIGQUIT, SIG_DFL);
	}
	else
	{
		init_signal_handler(SIGINT, &sig_noninteractive);
		init_signal_handler(SIGQUIT, &sig_noninteractive);
	}
}
