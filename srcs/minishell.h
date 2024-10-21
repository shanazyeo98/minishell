/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/10/21 14:00:05 by mintan           ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

/* General */
# define DELIMITER " '\"$?"
# define PROMPT "٩(ఠ益ఠ)۶ > "
# define EXIT_CMD "exit"
# define EXIT_MSG "Goodbye\n"
# define HEREDOCFILE "heredoc"
# define HEREDOCPROMPT "໒(⊙ᴗ⊙)७✎▤ > "
# define HEREDOCOP "<<"
# define APPENDOP ">>"
# define INPUTOP "<"
# define OUTPUTOP ">"

/* Error messages */
# define ERR_MALLOC_FAIL "Malloc failed. Exiting the programme now. Goodbye."
# define ERR_SIGACTION_FAIL "Signal handler registration failed. Goodbye."
# define ERR_SYNTAX "ಥ_ಥ : Syntax error"
# define ERR "ಥ_ಥ"

# define OPEN 0
# define CLOSED 1
# define TRUE 1
# define FALSE 0
# define INTERACTIVE 0
# define NONINTERACTIVE 1
# define CDPATH "CDPATH"
# define HOME "HOME"
# define PWD "PWD"

//global variable

extern int	g_sig_status;

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
	int				fd;
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

struct		s_cmd;

typedef struct s_redir
{
	int		id;
	char	*file;
	int		fd;
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
	t_redir	**redir;
}	t_cmd;

//file type

typedef struct s_cd
{
	char	*path;
	char	**cdpath;
}	t_cd;


//overall data structure

enum	e_exitstat
{
	SUCCESS = 0,
	ERROR = 1,
	INVALIDUSAGE = 2,
	PERMISSIONERR = 126,
	CMDNOTFOUND = 127,
	FAIL = 256,
};

typedef struct s_minishell
{
	t_list	*envp;
	char	**path;
	char	*input;
	t_token	**tokenlist;
	char	connector[4];
	char	operator[3];
	char	redirector[3];
	char	*validopre[8];
	int		hdcount;
	int		hd_expand;
	char	*cwd;
	int		exitstatus;
//	int		pid;
//	char	*delim;
	t_ast	*ast;
}	t_minishell;

/* Initialisation functions */
void		declarearray(t_minishell *params);
char		**getpaths(void);
void		getinput(t_minishell *ms);
t_minishell	init_ms(int argc, char *argv[], char *envp[]);
int			rl_empty_event(void);

/* Environment funtions */
t_list		*stray_to_llist(char **str);
char		**llist_to_stray(t_list *llist);
t_list		*find_env_var(char *var, t_list *envp);
char		*retrieve_env_var(char *var, t_list *envp, int *status);
char		*substring_after_char(char *input, char delim);

/* Signal functions */
void		init_all_sig_handler(int state);
void		init_signal_handler(int signum, void (*func)(int));
void		sig_handler(int signum);

//tokens
t_token			*lsttoken(t_token *token);
int				assigntoken(int type, t_tokendets *info, t_minishell *params);
int				newtoken(char a, t_minishell *params, t_tokendets *info, int i);
int				chartype(char a, t_minishell *params);
int				readchar(char a, t_minishell *params, t_tokendets *info, int *i);
int				returntype(char a, t_minishell *params);
int				closetoken(t_tokendets *info, int i, t_token *open);
int				chartype(char a, t_minishell *params);
int				checkend(t_minishell *params, t_tokendets *info);
void			tokenize(char *prompt, t_minishell *params);
void			freetokens(t_token **list);
t_token			*ret_token(int id, t_token *token);
void			print_token_list(t_minishell ms);

//heredoc
int			heredoc(int hd, t_token *token, char *delim, t_minishell *params);
void		heredoccheck(t_token **tokenlist, t_minishell *params);
char		*delim(t_token *token, t_minishell *params);
int			herefile(int hd);

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

/* Expansion functions*/
int			token_parameter_expansion(t_token *token, t_list *envp, int exit_status);
char		*substring_after_char(char *input, char delim);
char		*retrieve_env_var(char *var, t_list *envp, int *status);

/* AST utils */
void		print_ast_node(t_ast *node);
void		print_ast_cmd(t_token *start, t_token *end);
void		print_ast(t_ast *node, int ctr);
void		traverse_ast_first_last(t_ast *node);

//update tree
void		count(int *args, int *redir, t_cmd *cmd);
int			countargs(char *str, t_token *token, t_cmd *cmd);
int			redirection(t_cmd *cmd, t_token **token, t_redir **redir);
int			ft_assignstr(char *newstr, char **args);
int			fill(t_cmd *cmd);
void		free_tree(t_ast *node);

//cd
int			checkslash(char *str);
char		*genpath(char *currdir, char *relpath);
int			changedir(char *dir, char *path, t_minishell *params, int rel);
int			checkdirexists(char *path);
int			gotorelative(char *dir, t_minishell *params);
int			checkfileexists(char *path);
void		cderrormsg(char *dir);
int			cd(char **args, t_minishell *params);

//builtin general
int			countexeargs(char **args);
int			builtin_env(char **arg, t_list **envp);
int			builtin_unset(char **arg, t_list **envp);


/* Clean up functions */
void		free_ft_split(char **arr);
void		spick_and_span(t_minishell *ms, int status);
void		break_shell(t_minishell *ms);

#endif
