/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/10/22 18:13:03 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Description: Retrieves a variable name from an input string. Searches up to
   char c within the input string using ft_strchr. If 'c' does not exist within
   the input string, the whole string is the variable name. Uses a ft_strdup or
   ft_substr to return a variable name
*/

char	*get_var_name(char *in, char c)
{
	char	*var;

	if (ft_strchr(in, c) == NULL)
		var = ft_strdup(in);
	else
		var = ft_substr(in, 0, ft_strchr(in, c) - in);
	return (var);
}


/* Description: takes in an array of strings containing the environment
   variables and their corresponding values. For each environment variable,
   search through the envp linked list for a match and remove that node if
   there is a match. Add the whole string into the envp linked list after.
*/

t_list	**add_var(t_list **envp, char **args)
{
	char	*var;
	int		i;
	t_list	*found;
	t_list	*add;

	i = 1;
	while (args[i] != NULL)
	{
		var = get_var_name(args[i], '=');
		if (var == NULL)
			return (NULL);
		found = find_env_var(var, *envp);
		free (var);
		var = NULL;
		if (found != NULL)
			ft_lstrm_node(envp, found);
		var = ft_strdup(args[i]);
		if (var == NULL)
			return (NULL);
		add = ft_lstnew(var);
		if (add == NULL)
			return (free (var), NULL);
		ft_lstadd_back(envp, add);
		i++;
	}
	return (envp);
}







// int	main(void)
// {
// 	char	*in1;
// 	char	*in2;
// 	char	*in3;
// 	char	*in4;

// 	in1 = "var1";
// 	in2 = "var2=t2";
// 	in3 = "var3=longasssthingyhere=";
// 	in4 = "var5+t4";

// 	printf("in: %s | out: %s\n", in1, get_var_name(in1, '='));
// 	printf("in: %s | out: %s\n", in2, get_var_name(in2, '='));
// 	printf("in: %s | out: %s\n", in3, get_var_name(in3, '='));
// 	printf("in: %s | out: %s\n", in4, get_var_name(in4, '='));


// }
