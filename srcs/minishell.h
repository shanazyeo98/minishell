/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/02 12:04:36 by shayeo           ###   ########.fr       */
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

# define OPEN 0
# define CLOSED 1

enum	e_exitstat
{
	SUCCESS,
	FAIL,
	ERROR,
};

enum	e_token
{
	BASIC,
	SINGLE,
	DOUBLE,
	OPERATOR,
	REDIRECTOR
};

enum	e_character
{
	CONNECTOR,
	REDIRECTION,
	OPERATION,
	OTHERS
};

typedef struct s_token
{
	int				type;
	char			*str;
	int				wordgrp;
	int				grp;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tokendets
{
	char	*prompt;
	int		wordgrp;
	int		grp;
	int		status;
	int		start_i;
}	t_tokendets;

typedef struct s_minishell
{
	char	**path;
	char	*input;
	t_token	**tokenlist;
	char	connector[4];
	char	operator[3];
	char	redirector[3];
	char	*validopre[8];
}	t_minishell;

/* Initialisation functions */
void	declarearray(t_minishell *params);
char		**getpaths(void);
void		getinput(t_minishell *ms);
t_minishell	init_ms(void);

//tokens
t_token	*lsttoken(t_token *token);
int		assigntoken(int type, t_tokendets *info, t_minishell *params);
int		newtoken(char a, t_minishell *params, t_tokendets *info, int i);
int		chartype(char a, t_minishell *params);
int		readchar(char a, t_minishell *params, t_tokendets *info, int *i);
int		returntype(char a, t_minishell *params);
int		closetoken(t_tokendets *info, int i, t_token *open);
int		chartype(char a, t_minishell *params);
int		checkend(t_minishell *params, t_tokendets *info);
int		tokenize(char *prompt, t_minishell *params);

/* Clean up functions */
void		free_ft_split(char **arr);

#endif
