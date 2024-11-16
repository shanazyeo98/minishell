/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/11/16 16:08:47 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: formats the value of the variable before it is printed. Adds a
   \ in front of any $ encountered. Used in the export_print function.
   Format:
	- key="{value}"
	- key="{\$}"
*/

void	print_varlue(char *key, char *varlue)
{
	int	i;

	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	i = 0;
	while (varlue[i] != '\0')
	{
		if (varlue[i] == '$')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(varlue[i], STDOUT_FILENO);
		i++;
	}
	ft_putendl_fd("\"", STDOUT_FILENO);
}
