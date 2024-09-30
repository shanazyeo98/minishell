/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 03:41:04 by mintan            #+#    #+#             */
/*   Updated: 2024/10/01 04:14:57 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"



void	handler(int signum)
{
	printf("Caught signal %d\n", signum);
}




/* Description:
*/

void	init_signals(void)
{
	struct sigaction act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	// act.sa_flags == 0;
	sigaction(SIGINT, &act, NULL);
}

