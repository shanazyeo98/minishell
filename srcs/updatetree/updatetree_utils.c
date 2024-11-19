/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatetree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:32:01 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/19 15:39:27 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		countstr(const char *s)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	if (s == NULL)
		return (0);
	while (s[index] != '\0')
	{
		if (ft_isspace(s[index]) != 1 && (ft_isspace(s[index + 1]) == 1 \
		|| s[index + 1] == '\0'))
			count++;
		index++;
	}
	return (count);
}

static int	ft_indivlen(char const *s, int start)
{
	int		count;

	count = 0;
	while (ft_isspace(s[start + count]) != 1 && s[start + count] != '\0')
	{
		count++;
	}
	return (count);
}

static void	*ft_delete(char **array, int arr_index)
{
	int		index;

	index = 0;
	while (index < arr_index)
	{
		free(array[index]);
		index++;
	}
	free (array);
	return (NULL);
}

char	**split(char const *s)
{
	char	**array;
	int		arr_index;
	int		start;
	char	*indiv_ptr;

	array = malloc((countstr(s) + 1) * sizeof(char *));
	if (array == NULL)
		return (array);
	arr_index = 0;
	start = 0;
	while (arr_index < countstr(s))
	{
		if (ft_indivlen(s, start) != 0)
		{
			indiv_ptr = ft_substr(s, start, ft_indivlen(s, start));
			if (indiv_ptr == NULL)
				return (ft_delete(array, arr_index));
			array[arr_index] = indiv_ptr;
			arr_index++;
		}
		start += ft_indivlen(s, start) + 1;
	}
	array[arr_index] = NULL;
	return (array);
}
