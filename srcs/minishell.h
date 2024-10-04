/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/04 09:02:57 by mintan           ###   ########.fr       */
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

/* General */
# define PROMPT "٩(ఠ益ఠ)۶ > "
# define EXIT_CMD "exit"
# define EXIT_MSG "Goodbye\n"

// /* Signal handling - Global variable to indicate if a signal is recieved*/
// extern	volatile sig_atomic_t	prompt_again;

/* Error messages */
# define ERR_MALLOC_FAIL "Malloc failed. Exiting the programme now. Goodbye."
# define ERR_SIGACTION_FAIL "Error registering signal handler. Exiting the programme now. Goodbye."

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
int			rl_empty_event(void);


/* Signal functions */
void		init_all_sig_handler(void);
void		init_signal_handler(int signum);
void		sig_handler(int signum);


/* xx functions xx*/



/* Clean up functions */
void		free_ft_split(char **arr);
void		spick_and_span(t_minishell ms);
void		break_shell(t_minishell *ms);

#endif
