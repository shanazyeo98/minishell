CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCS = srcs/main.c \
srcs/init_general.c \
srcs/signals_init.c \
srcs/cleanup.c \
srcs/declarechar.c \
srcs/heredoc.c \
srcs/heredoc_utils.c \
srcs/token_checktype.c \
srcs/token_list.c \
srcs/token_new.c \
srcs/token_read.c \
srcs/tokenize.c \
srcs/token_expand.c \
srcs/token_utils.c \
srcs/parse_branch.c \
srcs/parse_free.c \
srcs/parse_fillcmd.c \
srcs/parse_ops.c \
srcs/parse_retrievetype.c \
srcs/parse.c \
srcs/env_init.c \
srcs/env_retrieve.c \
srcs/ast_utils.c \
srcs/builtin_cd.c \
srcs/builtin_cd_relative.c \
srcs/builtin_cd_utils.c \
srcs/builtin_echo.c \
srcs/builtin_pwd.c \
srcs/builtin_exit.c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = libft.a
LIB = -lreadline
HEADERS = srcs/minishell.h
MAC_INCLUDE = -I/opt/homebrew/opt/readline/include
MAC_LIB = -L/opt/homebrew/opt/readline/lib

all: $(NAME)

bonus: $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(LIB) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

srcs/%.o: srcs/%.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make clean -C ./$(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
