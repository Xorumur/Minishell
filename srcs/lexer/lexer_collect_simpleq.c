#include "../../includes/minishell.h"

char	*lexer_collect_simplq_two(t_lexer *lexer, char *values, char *str)
{
	str = lexer_get_current_char_as_string(lexer, 0);
	values = ft_realloc(values, (ft_strlen(values) + ft_strlen(str) + 1));
	ft_strlcat(values, str, ft_strlen(values) + ft_strlen(str) + 1);
	if (str)
		free(str);
	lexer_advance(lexer);
	return (values);
}

t_token	*lexer_collect_simpleq(t_lexer *lexer)
{
	char	*values;

	lexer_advance(lexer);
	values = malloc(1);
	if (!values)
		return (NULL);
	values[0] = '\0';
	while ((lexer->c != '\''))
	{
		if (lexer->c == '\0')
		{
			g_data.quoterror = 1;
			free(values);
			return (init_token(TK_SIMPLQ, NULL));
		}
		values = lexer_collect_simplq_two(lexer, values, NULL);
	}
	lexer_advance(lexer);
	return (init_token(TK_SIMPLQ, values));
}

/*
 ** Return the token for a simpleq (used in lexer_get_next_token)
 */
t_token	*lexer_string_simpleq(t_lexer *lexer, t_token *string)
{
	string = lexer_collect_simpleq(lexer);
	if (string == NULL)
		return (NULL);
	else
		return (string);
	return (string);
}
