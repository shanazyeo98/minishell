/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:29:26 by shayeo            #+#    #+#             */
/*   Updated: 2024/05/22 16:34:49 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function: Writes string s followed by a new line to the file descriptor
Return: None
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, sizeof(char));
		s++;
	}
	write(fd, "\n", sizeof(char));
}
