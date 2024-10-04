/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_retrievetype.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:23:27 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 23:25:16 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_op(char *str)
{
	if (ft_strcmp(str, "&&") == 0)
		return (AND);
	if (ft_strcmp(str, "||") == 0)
		return (OR);
	return (PIPE);
}

int ret_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (INPUT);
	if (ft_strcmp(str, ">") == 0)
		return (OUTPUT);
	if (ft_strcmp(str, ">>") == 0)
		return (OUTPUT);
	return (HEREDOC);
}
