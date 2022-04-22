NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRCS =	main.c \
		srcs/free.c \
		srcs/signals.c \
		srcs/builtins/builtins1.c \
		srcs/builtins/builtins2.c \
		srcs/builtins/norme_export.c\
		srcs/builtins/norme_export2.c\
		srcs/builtins/echo_clean.c\
		srcs/builtins/norme_echo.c\
		srcs/builtins/echo.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/env.c \
		srcs/chained_list.c \
		srcs/lexer/lexer.c \
		srcs/lexer/lexer_collect_id.c \
		srcs/lexer/lexer_collect_arrow.c \
		srcs/lexer/lexer_collect_simpleq.c \
		srcs/lexer/lexer_collect_string.c \
		srcs/lexer/lexer_utils.c \
		srcs/parsing/parsing.c \
		srcs/parsing/handle_error.c \
		srcs/parsing/handle_error2.c \
		srcs/parsing/parsing2.c \
		srcs/builtins/export_clean.c\
		srcs/parsing/help_exec.c\
		srcs/parsing/norminette_friendly.c\
		srcs/parsing/norminette_friendly2.c\
		#srcs/builtins/export.c \
		srcs/builtins/export2.c \
		

OBJS = $(SRCS:.c=.o)

all:		libft $(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) ./libft/libft.a -lreadline -lncurses \
			-L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -o $(NAME)

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