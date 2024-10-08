/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/08 18:37:31 by mintan           ###   ########.fr       */
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
# define ERR_SYNTAX "ಥ_ಥ : Syntax error"

# define OPEN 0
# define CLOSED 1

//token data structure

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
	int				id;
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
	int		id;
}	t_tokendets;

//ast data structure

enum	e_node
{
	CMD,
	OP
};

enum	e_operators
{
	AND,
	OR,
	PIPE,
	NIL
};

enum	e_redirectors
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
};

struct	s_cmd;

typedef struct s_redir
{
	int		id;
	char	*file;
}	t_redir;

typedef struct s_ast
{
	int				id;
	int				type;
	int				op;
	int				grp;
	struct s_ast	*up;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_cmd	*cmd;
}	t_ast;

typedef struct s_cmd
{
	t_token	*start;
	t_token	*end;
	char	**args;
	int		n_redir;
	t_redir	**redir;
	t_ast	*up;
}	t_cmd;

//overall data structure

enum	e_exitstat
{
	SUCCESS,
	FAIL,
	ERROR,
};

typedef struct s_minishell
{
	char	**path;
	char	*input;
	t_token	**tokenlist;
	char	connector[4];
	char	operator[3];
	char	redirector[3];
	char	*validopre[8];
	t_ast	*ast;
}	t_minishell;

/* Initialisation functions */
void		declarearray(t_minishell *params);
char		**getpaths(void);
void		getinput(t_minishell *ms);
t_minishell	init_ms(void);

//tokens
t_token		*lsttoken(t_token *token);
int			assigntoken(int type, t_tokendets *info, t_minishell *params);
int			newtoken(char a, t_minishell *params, t_tokendets *info, int i);
int			chartype(char a, t_minishell *params);
int			readchar(char a, t_minishell *params, t_tokendets *info, int *i);
int			returntype(char a, t_minishell *params);
int			closetoken(t_tokendets *info, int i, t_token *open);
int			chartype(char a, t_minishell *params);
int			checkend(t_minishell *params, t_tokendets *info);
void		tokenize(char *prompt, t_minishell *params);
void		freetokens(t_token **list);
t_token		*ret_token(int id, t_token *token);

//parsing
int			ret_op(char *str);
int			ret_redir(char *str);
t_ast		*createnode(int id, int type, int op, int grp);
void		addleftnode(t_ast **branch, t_ast *new);
void		adduppernode(t_ast **branch, t_ast *new);
t_ast		*createbranch(t_token *token, int grp);
t_cmd		*createcmd(t_token *token);
t_ast		*parse(t_token *token, int id);
int			ret_grp(t_token *token, int basegrp);
void		branch_error(t_ast *branch);
void		tree_error(t_ast *node);

/* AST Traversal */
void	print_ast_node(t_ast *node);
void	print_cmds_first_last(t_ast *node);


/* Clean up functions */
void		free_ft_split(char **arr);

#endif
