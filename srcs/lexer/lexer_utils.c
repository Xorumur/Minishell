#include "../../includes/minishell.h"

void	lexer_back(t_lexer *lexer)
{
	lexer->i -= 1;
	lexer->c = lexer->content[lexer->i];
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_isspace_skip(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

int	ft_isprint_token(int c)
{
	if (c == '\"' || c == '=' || c == ' '
		|| c == '|' || c == '\'')
		return (1);
	else
		return (0);
}
