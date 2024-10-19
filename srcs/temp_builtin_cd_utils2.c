/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_builtin_cd_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:16:34 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/19 14:23:51 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//KIV on whether we need to implement logical path or physical path

#include "minishell.h"

int	gennewstr(char **current, int f_index, int l_index, int rel)
{
	char	*firsttemp;
	char	*secondtemp;
	char	*new;

	firsttemp = ft_substr(*current, 0, f_index);
	if (firsttemp == NULL)
		return (NULL);
	if ((*current)[l_index] != '\0')
	{
		secondtemp = ft_substr(*current, l_index, ft_strlen(*current));
		if (secondtemp == NULL)
			return (free(firsttemp), NULL);
		new = ft_strjoin(firsttemp, secondtemp);
		if (new == NULL)
			return (free(firsttemp), free(secondtemp), NULL);
	}
	else
		new = firsttemp;
	printf("new: %s\n", new);
	if (rel == TRUE)
		free(*current);
	*current = new;
}
