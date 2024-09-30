/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/30 13:28:06 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <time.h>

/* Error messages */
# define ERR_MALLOC_FAIL "Malloc failed. Exiting the programme now. Goodbye"

enum	token
{
	BASIC,
	SINGLE,
	DOUBLE,
	OPERATOR,
	REDIRECTOR
};

typedef struct	s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct	s_minishell
{
	char	**path;
	char	*input;
	t_token	**tokenlist;
}	t_minishell;

/* Initialisation functions */
char		**getpaths(void);
void		getinput(t_minishell *ms);
t_minishell	init_ms(void);

/* xx functions xx*/



/* Clean up functions */
void		free_ft_split(char **arr);

#endif
