/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/09 08:32:59 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: main programme for minishell

*/

int	main(void)
{
	t_minishell	ms;

	ms = init_ms();
//	printf("Test paths: %s\n", ms.path[0]);
	while (1)
	{
		getinput(&ms);
//		printf("Test print input: %s\n", ms.input);
		tokenize(ms.input, &ms);
		ms.ast = parse(*ms.tokenlist, -1);
		// print_cmds_first_last(ms.ast);
		print_ast(ms.ast, 0);


	}
	return (EXIT_SUCCESS);
	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct
	//Clean up
}
