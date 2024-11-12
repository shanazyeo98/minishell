/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:15 by shayeo            #+#    #+#             */
/*   Updated: 2024/11/12 18:02:09 by mintan           ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>

/* General */
# define DELIMITER " '\n\"$?"
# define PROMPT "٩(ఠ益ఠ)۶ > "
# define EXIT_CMD "exit"
# define EXIT_MSG "Goodbye\n"
# define HEREDOCFILE "heredoc"
# define HEREDOCFINAL "heredocfinal"
# define HEREDOCPROMPT "໒(⊙ᴗ⊙)७✎▤ > "
# define HEREDOCOP "<<"
# define APPENDOP ">>"
# define INPUTOP "<"
# define OUTPUTOP ">"
# define OPEN 0
# define CLOSED 1
# define TRUE 1
# define FALSE 0
# define INTERACTIVE 0
# define NONINTERACTIVE 1
# define CDPATH "CDPATH"
# define HOME "HOME"
# define PWDVAR "PWD"
# define EXPORTCMD "export"
# define ENVCMD "env"
# define EXITCMD "exit"
# define CDCMD "cd"
# define PWDCMD "pwd"
# define UNSETCMD "unset"
# define ECHOCMD "echo"

# define EXITCMDMSG "(´• ω •`)ﾉ	bye"

/* Error messages */
# define ERR_MALLOC_FAIL "Malloc failed. Exiting the programme now. Goodbye."
# define ERR_SIGACTION_FAIL "Signal handler registration failed. Goodbye."
# define ERR_SYNTAX "ಥ_ಥ : Syntax error"
# define ERR "ಥ_ಥ "
# define ERRCOLON "ಥ_ಥ : "

/*Extra*/

# define POSITIVECMD "hey"
# define FLIRTCMD "flirt"
# define DUCKCMD "quack"
# define CONDUCKCMD "confusedquack"
# define SOPHDUCKCMD "sophisticatedquack"
# define DEPRESSCMD "de"

# define POSITIVEMSG0 "keep shining! \U0001F4AB"
# define POSITIVEMSG1 "you're egg-cellent! \U0001F373"
# define POSITIVEMSG2 "you've got this! \U0001F64C"
# define POSITIVEMSG3 "remember to drink water \U0001FAF6"
# define POSITIVEMSG4 "you're tea-riffic! \U0001F375"
# define POSITIVEMSG5 "you're doing good! \U0001F90D"
# define POSITIVEMSG6 "donut give up! \U0001F369"

# define FLIRT0 "if you were a triangle, you'd be acute one  (>᎑<๑)/♡"
# define FLIRT1 "i must be an exception because you have sure caught me (>ᴗ•) !"
# define FLIRT2 "are you double? because you always float in my mind (⸝⸝ᵕᴗᵕ⸝⸝)"
# define FLIRT3 "are you a for loop? because you repeat in my mind (✿ᴗ͈ˬᴗ͈)⁾⁾"

# define DEE0 "you're proof that broken things can still be beautiful"
# define DEE1 "the light at the end of the tunnel might be an oncoming train"
# define DEE2 "this is the worst day of my life... so far"
# define DEE3 "Why chase dreams when reality will always catch up?"
# define DEE4 "Just because you haven't found the right person..."
# define DEE5 "It doesn't mean you will"

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
	int				hd_expand;
	char			*hd_content;
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

struct		s_cmdnode;

typedef struct s_ast
{
	int					id;
	int					type;
	int					op;
	int					grp;
	struct s_ast		*up;
	struct s_ast		*left;
	struct s_ast		*right;
	struct s_cmdnode	*cmdnode;
}	t_ast;

typedef struct s_redir
{
	int		id;
	char	*file;
	int		fd;
	int		hd_expand;
	char	*hd_content;
}	t_redir;

typedef struct s_cmd
{
	t_redir	**redir;
	char	**args;
}	t_cmd;

typedef struct s_cmdnode
{
	t_token	*start;
	t_token	*end;
	t_list	*cmds;
}	t_cmdnode;

//file type

typedef struct s_cd
{
	char	*path;
	char	**cdpath;
}	t_cd;

//wildcard

typedef struct s_wc
{
	char	*str;
	int		wildcard;
}	t_wc;

//builtins
enum	e_builtin
{
	ECHO,
	PWD,
	FLIRT,
	POSITIVE,
	DUCK,
	CONDUCK,
	SOPHDUCK,
	DEPRESS,
	EXPORT,
	EXIT,
	ENV,
	CD,
	UNSET
};

//overall data structure

enum	e_exitstat
{
	SUCCESS = 0,
	ERROR = 1,
	INVALIDUSAGE = 2,
	NOTEXECUTABLE = 126,
	CMDNOTFOUND = 127,
	FATALSIGNAL = 128,
	FAIL = 256,
};

typedef struct s_minishell
{
	t_list	*envp;
	char	**envp_arr;
	char	**paths;
	char	*input;
	t_token	**tokenlist;
	char	connector[4];
	char	operator[3];
	char	redirector[3];
	char	*validopre[8];
	int		hdcount;
	char	*cwd;
	int		exitstatus;
	int		hd_expand;
	int		*pid;
	int		fd1[2];
	int		fd2[2];
	int		exe_index;
	t_ast	*ast;
}	t_minishell;

/* Initialisation functions */
void		declarearray(t_minishell *params);
void		getinput(t_minishell *ms);
t_minishell	init_ms(int argc, char *argv[], char *envp[]);
int			rl_empty_event(void);

/* Environment funtions */
t_list		*stray_to_llist(char **str);
char		**llist_to_stray(t_list *llist);
t_list		*find_env_var(char *var, t_list *envp);
char		*retrieve_env_var(char *var, t_list *envp, int *status);
char		*substring_after_char(char *input, char delim);
int			populate_env_and_paths(t_minishell *params);
int			getpaths(t_minishell *params);

/* Signal functions */
void		init_all_sig_handler(int state);
void		init_signal_handler(int signum, void (*func)(int));
void		sig_handler(int signum);

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
void		print_token_list(t_minishell ms);
t_token		*ret_tokenwordgrp(int wordgrp, t_token *token);

//heredoc
int			heredoc(t_token *token, char *delim, t_minishell *params);
void		heredoccheck(t_token **tokenlist, t_minishell *params);
char		*delim(t_token *token, t_minishell *params);
void		pipeheredoc(t_redir *redir, t_redir **list, t_minishell *params);

//parsing
int			ret_op(char *str);
int			ret_redir(char *str);
t_ast		*createnode(int id, int type, int op, int grp);
void		addleftnode(t_ast **branch, t_ast *new);
void		adduppernode(t_ast **branch, t_ast *new);
t_ast		*createbranch(t_token *token, int grp);
t_cmdnode	*createcmd(t_token *token);
t_ast		*parse(t_token *token, int id);
int			ret_grp(t_token *token, int basegrp);
void		branch_error(t_ast *branch);

/* Expansion functions*/
char		*substring_after_char(char *input, char delim);
char		*retrieve_env_var(char *var, t_list *envp, int *status);
char		*retrieve_param_name(char *str);
char		*replace_param(char *input, char *par_dollar, char *rep);
char		*replace_exit_status(char *input, int exit_status);
char		*find_and_replace_param(char *input, t_list *envp, char *found);
char		*parameter_expansion(char *input, t_list *envp, int exit_status);
int			check_dollar(char c);
int			token_expansion(t_token *token, t_list *envp, int exit_status);

/* AST utils */
void		print_ast_node(t_ast *node);
void		print_ast_tkn(t_token *start, t_token *end);
void		print_ast_cmd(t_list *cmds);
void		printcmdlist(t_list *node);
void		print_ast(t_ast *node, int ctr);
int			traverse_ast(t_ast *node, t_minishell *params);

//update tree
void		count(int *args, int *redir, t_token *start, t_token *end);
int			countargs(char *str, t_token *token, t_token *start, t_token *end);
int			ft_assignstr(char *newstr, char **args);
int			fill(t_cmd *cmd, t_token *start, t_token *end);
void		free_tree(t_ast *node);
int			initcmd(t_cmd *cmd, t_token *start, t_token *end);
void		initredirarray(t_redir **array, int count);
void		initchararray(char **array, int count);
void		updatetree(t_cmdnode *cmdnode, t_minishell *params);
char		*newstring(char *str, char *addstr);
int			redirection(t_token *end, t_token **token, t_redir **redir, int *i);

//redirections
int			expandheredoc(t_redir *redir, t_minishell *params);
int			amendheredoc(int newfd, int oldfd, t_minishell *params);
int			exe_redirection(t_redir **redir, t_minishell *params);
void		closeredirfds(t_redir **redir);
int			get_last_redir(int type, t_redir **redir);

//wildcard
int			searchdir(char **newstr, t_list *wclist, char *cwd);
int			wildcard_expansion(int grp, t_minishell *params);
int			searchstar(char *str, int start);
int			createnewstr(char **newstr, char **array);
void		swapstrings(char **str1, char **str2);

//execution
void		closepipe(int fd[2]);
int			openpipe(int fd[2]);
int			builtin(char *str);
int			exebuiltin(int func, char **args, t_minishell *params);
int			execute(t_cmdnode *node, t_minishell *params);
int			exe_chd(t_minishell *params, t_list *cmd, int count);

//cd
int			checkslash(char *str);
char		*genpath(char *currdir, char *relpath);
int			changedir(char *dir, char *path, t_minishell *params, int rel);
int			checkdirexists(char *path);
int			gotorelative(char *dir, t_minishell *params);
int			checkfileexists(char *path);
void		cderrormsg(char *dir);
int			checkmatchingpath(char *dir, char *path, char *cwd);

/* Export builtin functions*/
int			find_index(char *str, char c);
t_list		*extract_and_copy_node(t_list *node);
t_list		*clone_envp(t_list **envp);
int			export_print(t_list **sorted, t_list **envp);
int			add_var(t_list **envp, char **args);
int			builtin_export(char **args, t_list **envp);

//builtin general
int			countexeargs(char **args);
int			builtin_env(char **arg, t_list **envp);
int			builtin_unset(char **arg, t_list **envp);
int			cd(char **args, t_minishell *params);
int			echo(char **args);
int			pwd(char **args, t_minishell params);
int			builtin_exit(char **arg, t_minishell *params);

//extra
int			positivemsg(void);
int			flirtmsg(void);
int			duck(char **args);
int			sophduck(void);
int			depressedmsg(void);

/* Clean up functions */
void		free_ft_split(char **arr);
void		free_envp_arr_and_paths(t_minishell *ms);
void		spick_and_span(t_minishell *ms, int status, int end);
void		break_shell(t_minishell *ms);

#endif
