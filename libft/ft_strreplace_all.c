/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:49:21 by mintan            #+#    #+#             */
/*   Updated: 2024/10/29 15:48:16 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description: Checks if a character, "c" is contained within a set of
   characters, "str". Returns 1 if "c" is found within "str" and 0 if not.
*/

static	int	char_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

/* Description: Iteratively performs the followng steps until all "or" are
   replaced:
	1. Find the substring "or" within the input string,"in" using ft_strnstrn
	2. ft_substrings the left of "or" within "in"
	3. ft_strjoins the left with the replacement "rep"
	4. ft_substring the right of the "or" within "in"
	5. ft_strjoins the right of "or" within "in" to get the result
	e.g -left-or-right- --> left-rep-right
*/

char	*combine_string(char *in, char *or, char *rep, char *found)
{
	char	*left;
	char	*right;
	char	*res;
	char	*temp;

	left = ft_substr(in, 0, found - in);
	if (left == NULL)
		return (NULL);
	temp = ft_strjoin(left, rep);
	free (left);
	if (temp == NULL)
		return (NULL);
	right = ft_substr(in, found - in + ft_strlen(or), ft_strlen(in) - \
	(found - in + ft_strlen(or)));
	if (right == NULL)
	{
		free (temp);
		return (NULL);
	}
	res = ft_strjoin(temp, right);
	free (right);
	free (temp);
	free (in);
	return (res);
}

/* Description: Takes in an input string "in", and "or", a substring to be
   found within the "in", and "rep", the string to replace "or" and a string
   containing all the delimiters for "or", "delim". "or" is only valid for
   replacement if it is delimited by a character found within the set, "delim".
   If "delim", is "", this function replaces all instances "or" regardless of
   delimiters. The function calls the combine_string function iteratively
   until all the "or" are replaced. The function also frees the pointer to
   "in" and returns a new string with its own memory allocated.
*/

char	*ft_strreplace_all(char *in, char *or, char *rep, char *delim)
{
	char	*res;
	char	*found;
	char	*temp;
	size_t	or_len;

	res = in;
	temp = in;
	or_len = ft_strlen(or);
	found = ft_strnstr(in, or, ft_strlen(in));
	while (found != NULL)
	{
		if (char_str(found[or_len], delim) == 1 || ft_strcmp(found, or) == 0 \
		|| ft_strcmp(delim, "") == 0)
		{
			res = combine_string(temp, or, rep, found);
			if (res == NULL)
				return (NULL);
			temp = res;
			found = ft_strnstr(temp, or, ft_strlen(temp));
		}
	}
	return (res);
}
