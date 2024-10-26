/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:49:21 by mintan            #+#    #+#             */
/*   Updated: 2024/10/26 09:15:49 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../srcs/minishell.h"

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

/* Description: Inputs:
   	- in: input string
	- or: original substring within input "in" to be replaced
	- rep: the string to replaced "or" within "in"
	- found: the starting position of "or" within "in"
   Performs the following steps to replace "or":
	1. ft_substrings the left of "or" within "in"
	2. ft_strjoins the left with the replacement "rep"
	3. ft_substring the right of the "or" within "in"
	4. ft_strjoins the right of "or" within "in" to get the result
	e.g:
		- in: left-or-right
		- result: left-rep-right
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

/* Description: Inputs:
   	- in: input string
	- or: original substring within input "in" to be replaced
	- rep: the string to replaced "or" within "in"
	- delim: string containing all the delimiters for "or". "or" is only valid
	  for replacement if it is delimited by a character within the delim set.
	  If delim is "", "or" does not need to does not need to separated by a
	  delimiter to be replaced
  The function frees the pointer to "in" and returns a new string with its own
  memory allocated.
*/

char	*ft_strreplace_one(char *in, char *or, char *rep, char *delim)
{
	char	*res;
	char	*found;
	char	*temp;
	size_t	or_len;


	res = in;
	or_len = ft_strlen(or);
	found = ft_strnstr(in, or, ft_strlen(in));
	if (found != NULL)
	{
		if (char_str(found[or_len], delim) == 1 || ft_strcmp(found, or) == 0 \
		|| ft_strcmp(delim, "") == 0)
		{
			res = combine_string(in, or, rep, found);
			if (res == NULL)
				return (NULL);
		}
	}
	return (res);
}

int	main(void)
{
	char	*in1;
	char	*in2;
	char	*in3;
	char	*in4;

	char	*out1;
	char	*out2;
	char	*out3;
	char	*out4;



	in1 = ft_strdup("$?test");
	in2 = ft_strdup("$v1");
	in3 = ft_strdup("$v1? $v1\" '$v1' $v1$v2 $v1");
	in4 = ft_strdup("$v2? $v2\" '$v2' $v2$v3 $v4");

	printf("in1: %s\nin2: %s\nin3: %s\nin4: %s\n", in1, in2, in3, in4);

	out1 = ft_strreplace_one(in1, "$?", "rep", "");
	out2 = ft_strreplace_one(in2, "$v1", "rep", "");
	out3 = ft_strreplace_one(in3, "$v1", "rep", DELIMITER);
	out4 = ft_strreplace_one(in4, "$v4", "rep", DELIMITER);
	printf("o1: %s\no2: %s\no3: %s\no4: %s\n", out1, out2, out3, out4);

}
