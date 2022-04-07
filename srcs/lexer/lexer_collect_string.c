#include "../../includes/minishell.h"

char	*get_variable_env_lexer(t_lexer *lexer, char *values, char *str)
{
	char	*alphastr;

	alphastr = get_alpha_string(lexer);
	str = ft_getenv(alphastr);
	free(alphastr);
	values = ft_realloc(values, (ft_strlen(values) + ft_strlen(str) + 1));
	ft_strlcat(values, str, ft_strlen(values) + ft_strlen(str) + 1);
	free(str);
	return (values);
}

char	*lexer_collect_string_two(t_lexer *lexer, char *values, char *str)
{
	if (lexer->c == '$')
	{
		lexer_advance(lexer);
		if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c))
			values = get_variable_env_lexer(lexer, values, str);
		else if (lexer->c == '?')
		{
			lexer_advance(lexer);
			str = ft_itoa(g_data.exec);
			values = ft_realloc(values, (ft_strlen(values) + \
				ft_strlen(str) + 1));
			ft_strlcat(values, str, ft_strlen(values) + ft_strlen(str) + 1);
			free(str);
		}
	}
	else
	{
		str = lexer_get_current_char_as_string(lexer, 0);
		values = ft_realloc(values, (ft_strlen(values) + ft_strlen(str) + 1));
		ft_strlcat(values, str, ft_strlen(values) + ft_strlen(str) + 1);
		free(str);
		lexer_advance(lexer);
	}
	return (values);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer, int arr)
{
	char	*dest;

	dest = malloc(sizeof(char) * (arr + 2));
	if (!dest)
		exit(1);
	if (arr == 1)
	{
		dest[0] = lexer->c;
		dest[1] = '>';
		dest[2] = '\0';
		return (dest);
	}
	else if (arr == 2)
	{
		dest[0] = lexer->c;
		dest[1] = '<';
		dest[2] = '\0';
		return (dest);
	}
	dest[0] = lexer->c;
	dest[1] = '\0';
	return (dest);
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	*values;

	lexer_advance(lexer);
	values = malloc(1);
	if (!values)
		return (NULL);
	values[0] = '\0';
	while ((lexer->c != '"'))
	{
		if (lexer->c == '\0')
		{
			g_data.quoterror = TRUE;
			free(values);
			return (init_token(TK_STRING, NULL));
		}
		values = lexer_collect_string_two(lexer, values, NULL);
	}
	lexer_advance(lexer);
	return (init_token(TK_STRING, values));
}

/*
 ** Return the token for a string (used in lexer_get_next_token)
 */
t_token	*lexer_string(t_lexer *lexer, t_token *string)
{
	string = lexer_collect_string(lexer);
	if (string == NULL)
		return (NULL);
	else
		return (string);
	return (string);
}
