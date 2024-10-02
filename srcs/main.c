/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/10/02 12:04:55 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* Description: main programme for minishell

*/

int	main(void)
{
	t_minishell	ms;

	ms = init_ms();
	printf("Test paths: %s\n", ms.path[0]);
	while (1)			//use a global variable to store the signal for the while loop?
	{
		getinput(&ms);
		printf("Test print input: %s\n", ms.input);
		tokenize(ms.input, &ms);
	}




	return (EXIT_SUCCESS);




	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct
	//Clean up

}
