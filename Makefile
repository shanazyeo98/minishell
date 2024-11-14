CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCS = srcs/main.c \
srcs/execution/execution.c \
srcs/execution/execution_child.c \
srcs/execution/execution_heredoc.c \
srcs/execution/execution_redirection.c \
srcs/execution/execution_utils.c \
srcs/execution/execution_utils2.c \
srcs/general/init_general.c \
srcs/signals/signals_init.c \
srcs/general/cleanup.c \
srcs/general/declarechar.c \
srcs/heredoc/heredoc.c \
srcs/heredoc/heredoc_utils.c \
srcs/tokenizer/token_checktype.c \
srcs/tokenizer/token_list.c \
srcs/tokenizer/token_new.c \
srcs/tokenizer/token_read.c \
srcs/tokenizer/tokenize.c \
srcs/tokenizer/token_utils.c \
srcs/parser/parse_branch.c \
srcs/parser/parse_free.c \
srcs/parser/parse_fillcmd.c \
srcs/parser/parse_ops.c \
srcs/parser/parse_retrievetype.c \
srcs/parser/parse.c \
srcs/parser/ast_utils.c \
srcs/expansion/env_init.c \
srcs/expansion/env_retrieve.c \
srcs/expansion/token_expand.c \
srcs/expansion/expand_parameter.c \
srcs/expansion/expand_utils.c \
srcs/expansion/split_money.c \
srcs/expansion/wildcard.c \
srcs/expansion/wildcard_match.c \
srcs/expansion/wildcard_utils.c \
srcs/updatetree/updatetree.c \
srcs/updatetree/updatetree_cmd.c \
srcs/updatetree/updatetree_fill.c \
srcs/updatetree/updatetree_redirector.c \
srcs/builtins/builtin_cd.c \
srcs/builtins/builtin_cd_relative.c \
srcs/builtins/builtin_cd_utils.c \
srcs/builtins/builtin_echo.c \
srcs/builtins/builtin_pwd.c \
srcs/builtins/builtin_exit.c \
srcs/builtins/builtin_env.c \
srcs/builtins/builtin_unset.c \
srcs/builtins/builtin_export.c \
srcs/builtins/builtin_export_utils.c \
srcs/extra/extra.c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = libft.a
LIB = -lreadline
HEADERS = srcs/minishell.h
# MAC_INCLUDE = -I/opt/homebrew/opt/readline/include
# MAC_LIB = -L/opt/homebrew/opt/readline/lib

all: $(NAME)

bonus: $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(LIB) $(MAC_LIB) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

srcs/%.o: srcs/%.c $(HEADERS)
	$(CC) $(FLAGS) $(MAC_INCLUDE) -c $< -o $@

clean:
	make clean -C ./$(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
