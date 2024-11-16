/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:46:15 by mintan            #+#    #+#             */
/*   Updated: 2024/11/16 15:59:08 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Description: formats th
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
