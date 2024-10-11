CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCS = srcs/main.c \
srcs/init_general.c \
srcs/signals_init.c \
srcs/cleanup.c \
srcs/declarechar.c \
srcs/heredoc.c \
srcs/token_checktype.c \
srcs/token_list.c \
srcs/token_new.c \
srcs/token_read.c \
srcs/tokenize.c \
srcs/token_utils.c \
srcs/parse_branch.c \
srcs/parse_error.c \
srcs/parse_fillcmd.c \
srcs/parse_ops.c \
srcs/parse_retrievetype.c \
srcs/parse.c
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
