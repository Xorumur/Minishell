
NAME = minishell

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRCS =	main.c \
		srcs/free.c \
		srcs/signals.c \
		srcs/builtins/builtins1.c \
		srcs/builtins/builtins2.c \
		srcs/utils.c \
		srcs/env.c \
		srcs/chained_list.c \
		srcs/lexer/lexer.c \
		srcs/lexer/lexer_collect_id.c \
		srcs/lexer/lexer_collect_arrow.c \
		srcs/lexer/lexer_collect_simpleq.c \
		srcs/lexer/lexer_collect_string.c \
		srcs/lexer/lexer_utils.c \
		srcs/parsing/exec_line.c \
		srcs/parsing/parsing.c \


OBJS = $(SRCS:.c=.o)

all:		libft $(NAME)

# ./includes/libreadline.a

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) ./libft/libft.a -lreadline -lncurses -o $(NAME)

libft:
			make -C ./libft

clean:
			rm -f $(OBJS)
# make clean -C ./libft  // A remettre plus tard

fclean:		clean
			rm -f $(NAME)
# make fclean -C ./libft // A remettre plus tard

norme:
			norminette $(SRCS)

re:			fclean all

.PHONY:		re clean fclean all libft