CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCS = srcs/main.c srcs/init_general.c srcs/cleanup.c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = libft.a
LIB = -lreadline -lncurses
HEADERS = srcs/minishell.h
HEADERS_BONUS = bonus/minishell_bonus.h

all: $(NAME)

bonus: $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(LIB) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

srcs/%.o: srcs/%.c $(HEADERS)
	$(CC) $(FLAGS)  -c $< -o $@

clean:
	make clean -C ./$(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
