/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/26 09:47:53 by mintan           ###   ########.fr       */
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

	char		*env[2] = {"env", NULL};
	char		*exp1[2] = {"export", NULL};
	char		*exp2[8] = {"export", "va\%r", "v1=t1", "v2=t2", "v3=t3", "v4=t4", "v5=t5", NULL};



	ms = init_ms(argc, argv, envp);

	printf("====================Print env var====================\n");
	builtin_env(env, &ms.envp);

	printf("====================Print export====================\n");
	builtin_export(exp1, &ms.envp);

	printf("====================Export invalid var====================\n");
	builtin_export(exp2, &ms.envp);

	printf("====================Print export====================\n");
	builtin_export(exp1, &ms.envp);



	while (1)
	{
		init_all_sig_handler(INTERACTIVE);
		getinput(&ms);
		init_all_sig_handler(NONINTERACTIVE);
		if (ms.input == NULL) //|| ft_strcmp(ms.input, EXIT_CMD) == 0)
			break_shell(&ms);
		tokenize(ms.input, &ms);
		print_token_list(ms);
		token_parameter_expansion(*(ms.tokenlist), ms.envp, ms.exitstatus);
		print_token_list(ms);


		// if (ms.tokenlist != NULL)
		// {
		// 	heredoccheck(ms.tokenlist, &ms);
		// 	ms.ast = parse(*ms.tokenlist, -1);
		// 	execute(ms.ast->cmdnode, &ms);
		// }
		// printf("cwd: %s\n", ms.cwd);
		// spick_and_span(&ms, SUCCESS);
	}

	return (EXIT_SUCCESS);
}
