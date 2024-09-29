/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/09/30 06:57:37 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/* Description: main programme for minishell

*/

int	main(void)
{
	char	**paths;
	// char	*input;
	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct

	paths = getpaths();
	printf("[0]: %s | [1]: %s\n", paths[0], paths[1]);

	// while (1)			//use a global variable to store the signal for the while loop?
	// {
	// 	input = readline("٩(ఠ益ఠ)۶");
	// 	ft_printf("%s\n", input);
	// }




	//Clean up
	return (EXIT_SUCCESS);
}
