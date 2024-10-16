/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:34:35 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/16 10:40:11 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//wip - mainly to see how it works for symlinks

int	pwd(void)
{
	char		*dir;
	struct stat	buf;

	chdir("/home/codespace");
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		perror("");
		return (ERROR);
	}
	printf("dir: %s\n", dir);
	lstat(dir, &buf);
	printf("%ld\n", buf.st_ino);
	// printf("%s\n", dir);
	// free(dir);
	return (SUCCESS);
}

//testing
int	main(void)
{
	pwd();
}
