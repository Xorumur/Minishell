#include "../../includes/minishell.h"

/*
 ** init our struct lexer and setup the index and the cmd
 */
t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		exit(127);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

/*
 ** Malloc and setup the token for all returns in lexer_get_next_token
 */
t_token	*init_token(int type, char *value)
{
	t_token	*token;

	// if (!value)
	// 	return NULL;
	token = malloc(sizeof(t_token));
	if (!token)
		exit(127);
	token->e_type = type;
	token->value = value;
	return (token);
}

/*
 ** Function that mains the lexer, every call to lexer_get_next_token return the next token
 ** in our command, we loop to this functions to setup our token chained list
 */
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == '"')
			return (lexer_string(lexer, NULL)); // Return a token 'string' (")
		else if (lexer->c == '\'')
			return (lexer_string_simpleq(lexer, NULL)); // Return a token 'simple quote' (')
		else if (lexer->c == '=')
			return (lexer_advance_with_token(lexer, init_token(TK_EQUALS,
						lexer_get_current_char_as_string(lexer, 0)))); // Return a token 'equal' (=)
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TK_PIPE,
						lexer_get_current_char_as_string(lexer, 0)))); // Return a token 'pipe' (|)
		else if (lexer->c == '<')
			return (lexer_leftarrow(lexer)); // Return a token 'leftarr' (<)
		else if (lexer->c == '>')
			return (lexer_rightarrow(lexer)); // Return a token 'rightarr' (>)
		else if (lexer->c == ' ')
			lexer_isspace_skip(lexer); // Skips spaces every time lexer->c is a space
		else if (ft_isprint(lexer->c))
			return (lexer_collect_id(lexer)); // Return a token id when nothing else is detected
		else
			lexer_advance(lexer); // Increment lexer->i and change lexer->c to go to next token
	}
	return ((void *)0);
}