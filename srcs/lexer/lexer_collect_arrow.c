#include "../../includes/minishell.h"

/*
 ** Return the token for a left arrow (used in lexer_get_next_token)
 */
t_token	*lexer_leftarrow(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '<')
		return (lexer_advance_with_token(lexer, init_token(TK_D_ARR_L,
					lexer_get_current_char_as_string(lexer, 2))));
	else
	{
		lexer_back(lexer);
		return (lexer_advance_with_token(lexer, init_token(TK_ARR_L,
					lexer_get_current_char_as_string(lexer, 0))));
	}
	return (NULL);
}

/*
 ** Return the token for a right arrow (used in lexer_get_next_token)
 */
t_token	*lexer_rightarrow(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '>')
		return (lexer_advance_with_token(lexer, init_token(TK_D_ARR_R,
					lexer_get_current_char_as_string(lexer, 1))));
	else
	{
		lexer_back(lexer);
		return (lexer_advance_with_token(lexer, init_token(TK_ARR_R,
					lexer_get_current_char_as_string(lexer, 0))));
	}
	return (NULL);
}

