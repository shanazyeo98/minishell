/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:57:23 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/25 13:44:20 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	positivemsg(void)
{
	static int	i = 0;

	if (i % 7 == 0)
		ft_putendl_fd(POSITIVEMSG0, STDOUT_FILENO);
	if (i % 7 == 1)
		ft_putendl_fd(POSITIVEMSG1, STDOUT_FILENO);
	if (i % 7 == 2)
		ft_putendl_fd(POSITIVEMSG2, STDOUT_FILENO);
	if (i % 7 == 3)
		ft_putendl_fd(POSITIVEMSG3, STDOUT_FILENO);
	if (i % 7 == 4)
		ft_putendl_fd(POSITIVEMSG4, STDOUT_FILENO);
	if (i % 7 == 5)
		ft_putendl_fd(POSITIVEMSG5, STDOUT_FILENO);
	if (i % 7 == 6)
		ft_putendl_fd(POSITIVEMSG6, STDOUT_FILENO);
	i++;
	return (SUCCESS);
}

int	flirtmsg(void)
{
	static int	i = 0;

	if (i % 4 == 0)
		ft_putendl_fd(FLIRT0, STDOUT_FILENO);
	if (i % 4 == 1)
		ft_putendl_fd(FLIRT1, STDOUT_FILENO);
	if (i % 4 == 2)
		ft_putendl_fd(FLIRT2, STDOUT_FILENO);
	if (i % 4 == 3)
		ft_putendl_fd(FLIRT3, STDOUT_FILENO);
	i++;
	return (SUCCESS);
}

int	duck(void)
{
	ft_putendl_fd("           -----", STDOUT_FILENO);
	ft_putendl_fd("         < Quack >", STDOUT_FILENO);
	ft_putendl_fd("   _   /   -----", STDOUT_FILENO);
	ft_putendl_fd("__(•)> ", STDOUT_FILENO);
	ft_putendl_fd("\\___)", STDOUT_FILENO);
	return (SUCCESS);
}

int	confusedduck(void)
{
	ft_putendl_fd("           ----------", STDOUT_FILENO);
	ft_putendl_fd("  ?      < Huh? Quack >", STDOUT_FILENO);
	ft_putendl_fd("   _   /   ----------", STDOUT_FILENO);
	ft_putendl_fd("__(•)>", STDOUT_FILENO);
	ft_putendl_fd("\\___)", STDOUT_FILENO);
	return (SUCCESS);
}
