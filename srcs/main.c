/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/23 12:56:15 by shayeo           ###   ########.fr       */
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
	spick_and_span(ms, SUCCESS);
	exit(EXIT_SUCCESS);
}

/* Description: main programme for minishell
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;

	ms = init_ms(argc, argv, envp);
//	init_all_sig_handler();
	while (1)
	{
		g_sig_status = 0;
		init_all_sig_handler(INTERACTIVE);
		getinput(&ms);
		init_all_sig_handler(NONINTERACTIVE);
		if (ms.input == NULL) //|| ft_strcmp(ms.input, EXIT_CMD) == 0)
			break_shell(&ms);
		if (g_sig_status != SIGINT)
			tokenize(ms.input, &ms);
//		print_token_list(ms);
		if (ms.tokenlist != NULL)
		{
			heredoccheck(ms.tokenlist, &ms);
			ms.ast = parse(*ms.tokenlist, -1);
			execute(ms.ast->cmdnode, &ms);
		}
//		printf("cwd: %s\n", ms.cwd);
		spick_and_span(&ms, SUCCESS);
	}
	return (EXIT_SUCCESS);
}
