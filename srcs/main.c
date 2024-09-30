/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:11:07 by mintan            #+#    #+#             */
/*   Updated: 2024/09/30 09:09:54 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/* Description: main programme for minishell

*/

int	main(void)
{
	char	**paths;
	// char	*input;


	paths = getpaths();
	printf("Test paths: %s\n", paths[0]);
	while (1)			//use a global variable to store the signal for the while loop?
	{
		getinput();
	}





	// {
	// 	input = readline("٩(ఠ益ఠ)۶");
	// 	ft_printf("%s\n", input);
	// }






	return (EXIT_SUCCESS);




	//Logic
	//Might want to print smth to indicate the start of minishell
	//Init struct
	//Clean up

}
