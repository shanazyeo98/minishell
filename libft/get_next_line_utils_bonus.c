/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:52:49 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/23 15:25:08 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Functions to parse the buffer, detect if there is a new line and concat

#include "libft.h"

int	bufflen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	else
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

void	assignstr(char *dest, char *str, ssize_t stop)
{
	int	i;
	int	destlen;

	i = 0;
	destlen = bufflen(dest);
	while (i < stop)
	{
		dest[destlen + i] = str[i];
		i++;
	}
	dest[destlen + i] = '\0';
}

char	*concatbuffer(char *exist, char *new, ssize_t stop)
{
	char	*final;

	if (exist == NULL)
		final = malloc(stop + 1);
	else
		final = malloc(bufflen(exist) + stop + 1);
	if (final == NULL)
		return (NULL);
	final[0] = '\0';
	if (exist != NULL)
	{
		assignstr(final, exist, bufflen(exist));
		free(exist);
	}
	if (new != NULL)
		assignstr(final, new, stop);
	return (final);
}

int	parsebuffer(char *buffer)
{
	int	index;

	index = 0;
	if (buffer == NULL)
		return (-1);
	else
	{
		while (buffer[index] != '\0')
		{
			if (buffer[index] == '\n')
				return (index);
			index++;
		}
	}
	return (-1);
}

char	*rdbuffer(int fd, char *buffer, ssize_t *bread, char *remaining)
{
	*bread = read(fd, buffer, BUFFER_SIZE);
	if (*bread <= 0)
	{
		if (*bread < 0)
		{
			if (remaining != NULL)
			{
				free(remaining);
				remaining = NULL;
			}
		}
		return (remaining);
	}
	buffer[*bread] = '\0';
	remaining = concatbuffer(remaining, buffer, *bread);
	if (remaining == NULL)
		*bread = -1;
	return (remaining);
}
