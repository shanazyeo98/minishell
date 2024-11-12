/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/11/12 14:25:27 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: prints the exit message, cleans up all allocated memory, and
   exits the minishell programme. Function is used when Ctrl + D or the "exit"
   command is received.
*/
void	break_shell(t_minishell *ms)
{
	ft_putendl_fd(EXITCMDMSG, STDOUT_FILENO);
	spick_and_span(ms, SUCCESS, TRUE);
	exit(EXIT_SUCCESS);
}

/* Description: main programme for minishell
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;

	char		*i1;
	char		*i2;
	char		*i3;
	char		*i4;
	char		*i5;
	char		*i6;
	char		*i7;
	char		*i8;


	char		*o1;
	char		*o2;
	char		*o3;
	char		*o4;
	char		*o5;
	char		*o6;
	char		*o7;
	char		*o8;


	ms = init_ms(argc, argv, envp);


	i1 = ft_strdup("$");
	i2 = ft_strdup("$ ");
	i3 = ft_strdup("$ $v1");
	i4 = ft_strdup("$ $v1 $");
	i5 = ft_strdup("$ $v1$?$v2");
	i6 = ft_strdup("$ $v1$v1");
	i7 = ft_strdup("$ $v1 $ $v1");
	i8 = ft_strdup("$ $v1 $ $v1");


	o1 = parameter_expansion(i1, ms.envp, ms.exitstatus);
	printf("o1: %s\n", o1);

	o2 = parameter_expansion(i2, ms.envp, ms.exitstatus);
	printf("o2: %s\n", o2);

	o3 = parameter_expansion(i3, ms.envp, ms.exitstatus);
	printf("o3: %s\n", o3);

	o4 = parameter_expansion(i4, ms.envp, ms.exitstatus);
	printf("o4: %s\n", o4);

	o5 = parameter_expansion(i5, ms.envp, ms.exitstatus);
	printf("o5: %s\n", o5);

	o6 = parameter_expansion(i6, ms.envp, ms.exitstatus);
	printf("o6: %s\n", o6);

	o7 = parameter_expansion(i7, ms.envp, ms.exitstatus);
	printf("o7: %s\n", o7);

	o8 = parameter_expansion(i8, ms.envp, ms.exitstatus);
	printf("o8: %s\n", o8);







// 	while (1)
// 	{
// 		g_sig_status = 0;
// 		init_all_sig_handler(INTERACTIVE);
// 		getinput(&ms);
// 		if (ms.input == NULL)
// 			break_shell(&ms);
// 		if (g_sig_status != SIGINT)
// 			tokenize(ms.input, &ms);
// 		if (ms.tokenlist != NULL)
// 			heredoccheck(ms.tokenlist, &ms);
// 		init_all_sig_handler(NONINTERACTIVE);
// 		if (ms.tokenlist != NULL)
// 		{
// 			ms.ast = parse(*ms.tokenlist, -1);
// 			if (ms.ast == NULL)
// 				spick_and_span(&ms, FAIL, TRUE);
// 			ms.exitstatus = traverse_ast(ms.ast, &ms);
// 		}
// 		spick_and_span(&ms, SUCCESS, FALSE);
// 	}
// 	return (EXIT_SUCCESS);
}
