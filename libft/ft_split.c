/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:38:34 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/13 06:40:31 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Split the strings by the delimiter into an array of strings
Return:
1. Array of strings if successful
2. Else, NULL
QUESTION: When to use free()??
*/

#include "libft.h"
#include <stdio.h>

int	ft_countstr(char const *s, char c)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && (s[index + 1] == c || s[index + 1] == '\0'))
		{
			count++;
		}
		index++;
	}
	return (count);
}

static int	ft_indivlen(char const *s, char c, int start)
{
	int		count;

	count = 0;
	while (s[start + count] != c && s[start + count] != '\0')
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

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		arr_index;
	int		start;
	char	*indiv_ptr;

	array = malloc((ft_countstr(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (array);
	arr_index = 0;
	start = 0;
	while (arr_index < ft_countstr(s, c))
	{
		if (ft_indivlen(s, c, start) != 0)
		{
			indiv_ptr = ft_substr(s, start, ft_indivlen(s, c, start));
			if (indiv_ptr == NULL)
				return (ft_delete(array, arr_index));
			array[arr_index] = indiv_ptr;
			arr_index++;
		}
		start += ft_indivlen(s, c, start) + 1;
	}
	array[arr_index] = NULL;
	return (array);
}



// int	main(void)
// {
// 	char	*in;
// 	char	*in2;
// 	char	*in3;

// 	char	**out;
// 	char	**out2;
// 	char	**out3;


// 	in = ft_strdup("$123$$$?456$");
// 	in2 = ft_strdup("123$ $$?78 9$");
// 	in3 = ft_strdup("1234");


// 	printf("Original: %s\n", in);
// 	out = ft_split(in, '$');
// 	printf("-----Split results in-----\n");
// 	while (*out != NULL)
// 	{
// 		printf("res: %s\n", *out);
// 		*out++;
// 	}
// 	out2 = ft_split(in2, '$');
// 	printf("-----Split results in2-----\n");
// 	while (*out2 != NULL)
// 	{
// 		printf("res: %s\n", *out2);
// 		*out2++;
// 	}
// 	out3 = ft_split(in3, '$');
// 	printf("-----Split results in3-----\n");
// 	while (*out3 != NULL)
// 	{
// 		printf("res: %s\n", *out3);
// 		*out3++;
// 	}
// }
