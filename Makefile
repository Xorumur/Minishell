
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRCS =	main.c

OBJS = $(SRCS:.c=.o)

all:		libft $(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

libft:
			make -C ./libft

clean:
			rm -f $(OBJS)
			make clean -C ./libft

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft

norme:
			norminette $(SRCS)

re:			fclean all

.PHONY:		re clean fclean all libft