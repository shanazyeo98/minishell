/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/20 15:51:18 by mintan           ###   ########.fr       */
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
	char		*env_test[3] = {"env", NULL};
	int			status;

	ms = init_ms(argc, argv, envp);
	status = builtin_env(env_test, ms.envp);
	return (status);

	// while (1)
	// {
	// 	init_all_sig_handler(INTERACTIVE);
	// 	getinput(&ms);
	// 	init_all_sig_handler(NONINTERACTIVE);
	// 	if (ms.input == NULL || ft_strcmp(ms.input, EXIT_CMD) == 0)
	// 		break_shell(&ms);
	// 	tokenize(ms.input, &ms);
	// 	// print_token_list(ms);
	// 	if (ms.tokenlist != NULL)
	// 		heredoccheck(ms.tokenlist, &ms);

	// 	// printf("===============After token expansion===============\n");
	// 	// token_parameter_expansion(*ms.tokenlist, ms.envp, ms.exitstatus);
	// 	// print_token_list(ms);




	// 	if (ms.tokenlist != NULL)
	// 		ms.ast = parse(*ms.tokenlist, -1);
	// 	// print_ast(ms.ast, 0);
	// }
	// return (EXIT_SUCCESS);
}
