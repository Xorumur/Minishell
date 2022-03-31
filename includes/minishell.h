/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:28:23 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 18:16:49 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef int	t_bool;
# define TRUE 	1
# define FALSE 	0

/* === Struct for lexer === */
typedef struct s_lexer
{
	char			c;
	int	i;
	char			*content;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		TK_ID,
		TK_EQUALS,
		TK_STRING,
		TK_PIPE,
		TK_DOLAR,
		TK_ARR_L,
		TK_ARR_R,
		TK_D_ARR_L,
		TK_D_ARR_R,
		TK_SIMPLQ
	} e_type;
	char	*value;
}	t_token;

typedef struct s_tokenlist
{
	struct s_tokenlist	*prev;
	t_token				*token;
	struct s_tokenlist	*next;
}	t_tokenlist;

typedef struct s_env {
	struct s_env	*prev;
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_status {
	t_bool	is_env;			// is env valid ?
	t_bool	is_fork;		// are we in a fork ? (for signals)
	t_bool	is_redir;		// is there redir in cmd ?
	t_bool	is_pipe;		// is there pipes in cmd ?
	t_bool	is_heredoc;		// is there heredoc in cmd ? (double left redir)
}	t_status;


/* === Global Struct === */
typedef struct t_data {
	char			*cmd;		// curr cmd readline
	t_status		status;		// minishell status vars
	t_env			*env;

	t_lexer*		lexer;		// Lexer (every commands)
	t_tokenlist*	tokens;		// Token list (every commands is reseted)

	int				exec;		// Return number from cmds
	t_bool			quoterror;

}	t_data;

t_data		g_data;
/* ===================== */


void		rl_replace_line(const char *text, int clear_undo);


/* === ENV === */
void		init_data_env(char **env);
char		*ft_getenv(char *name);
void		print_env(t_env *env, int fd);

/* === UTILS / LIST === */
t_env		*ft_lstnew_env(char *name, char *content);
void		ft_lstadd_back_env(t_env **alst, t_env *new);
void		ft_lstadd_back_token(t_tokenlist **alst, t_tokenlist *new);
t_tokenlist	*ft_lstnew_token(t_token* token);
void		free_all(void);

char		*ft_realloc(char *src, int size);
void		free_tab(char **tableau);
void		print_tab(char **x);

/* === Builtins === */
void	cmd_export(char	*name, char *content, int fd);
void	cmd_echo(char	*mess, int option, int fd);
void	change_cd(char	*directory);
void	get_pwd(int fd);
void	cmd_env(int fd);
void	cmd_exit(int fd);
void	cmd_unset(char *name);


/* === SIGNALS === */
void	handle_sigquit(int sig);

/* === LEXER === */
t_token		*lexer_get_next_token(t_lexer *lexer);
t_token		*lexer_collect_id(t_lexer *lexer);
t_token		*lexer_string(t_lexer *lexer, t_token *string);
t_token		*lexer_string_simpleq(t_lexer *lexer, t_token *string);
t_token		*lexer_rightarrow(t_lexer *lexer);
t_token		*lexer_leftarrow(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_token		*init_token(int type, char *value);
t_lexer		*init_lexer(char *content);
void		lexer_back(t_lexer *lexer);
void		lexer_advance(t_lexer *lexer);
void		lexer_isspace_skip(t_lexer *lexer);
int			ft_isprint_token(int c);
char		*lexer_get_current_char_as_string(t_lexer *lexer, int arr);
char		*get_alpha_string(t_lexer *lexer);


#endif