/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/08 17:29:26 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Description: main programme for minishell
*/

int	main(void)
{
	t_minishell	ms;

	ms = init_ms();

	init_all_sig_handler();
	while (1)
	{
		getinput(&ms);
		if (ms.input == NULL || ft_strcmp(ms.input, EXIT_CMD) == 0)
			break_shell(&ms);
		tokenize(ms.input, &ms);
		ms.ast = parse(*ms.tokenlist, -1);
		//testing
//		printf("%d\n", mst);
	}
	return (EXIT_SUCCESS);
	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct
	//Clean up
}
