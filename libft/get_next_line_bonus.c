/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:42:13 by shayeo            #+#    #+#             */
/*   Updated: 2024/07/23 15:25:23 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extractstr(char *str, int n)
{
	char	*result;
	int		index;

	if (str == NULL)
		return (NULL);
	result = malloc(n + 1);
	if (result == NULL)
		return (NULL);
	index = 0;
	while (index < n)
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*rebuffer(char *buffer, int start)
{
	char	*newbuffer;
	int		i;

	i = 0;
	if (bufflen(buffer) - start > 0)
	{
		newbuffer = malloc(bufflen(buffer) - start + 2);
		if (newbuffer == NULL)
			return (NULL);
		while (start + i < bufflen(buffer))
		{
			newbuffer[i] = buffer[start + i];
			i++;
		}
		newbuffer[i] = '\0';
	}
	else
		newbuffer = NULL;
	if (buffer != NULL)
		free(buffer);
	return (newbuffer);
}

char	*endoffile(char **remaining)
{
	char	*result;

	result = extractstr(*remaining, bufflen(*remaining));
	if (*remaining != NULL)
	{
		free(*remaining);
		*remaining = NULL;
	}
	return (result);
}

char	*setparams(ssize_t *bread)
{
	char	*buffer;

	*bread = BUFFER_SIZE;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*remaining[1024];
	char			*result;
	int				nstatus;
	ssize_t			bread;
	char			*buffer;

	if (fd < 0)
		return (NULL);
	nstatus = parsebuffer(remaining[fd]);
	buffer = setparams(&bread);
	while (nstatus == -1 && bread == BUFFER_SIZE)
	{
		remaining[fd] = rdbuffer(fd, buffer, &bread, remaining[fd]);
		nstatus = parsebuffer(remaining[fd]);
	}
	if (buffer != NULL)
		free(buffer);
	if (nstatus >= 0)
	{
		result = extractstr(remaining[fd], nstatus + 1);
		remaining[fd] = rebuffer(remaining[fd], nstatus + 1);
	}
	else
		result = endoffile(&remaining[fd]);
	return (result);
}
