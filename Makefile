CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = libft.a
LIB = -lreadline
HEADERS = srcs/pipex.h
HEADERS_BONUS = bonus/pipex_bonus.h

all: $(NAME)

bonus: $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(LIB) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

srcs/%.o: srcs/%.c $(HEADERS)
	$(CC) $(FLAGS) $(LIB) -c $< -o $@

clean:
	make clean -C ./$(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
