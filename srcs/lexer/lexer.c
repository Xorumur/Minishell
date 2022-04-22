/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:18:08 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/20 11:49:02 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	token = malloc(sizeof(t_token));
	if (!token)
		exit(127);
	token->e_type = type;
	token->value = value;
	return (token);
}

/*
 ** Function that mains the lexer, every call to lexer_get_next_token 
 		return the next token
 ** in our command, we loop to this functions to setup our token chained list
 */
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == '"')
			return (lexer_string(lexer, NULL));
		else if (lexer->c == '\'')
			return (lexer_string_simpleq(lexer, NULL));
		else if (lexer->c == '=')
			return (lexer_advance_with_token(lexer, init_token(TK_EQUALS,
						lexer_get_current_char_as_string(lexer, 0))));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TK_PIPE,
						lexer_get_current_char_as_string(lexer, 0))));
		else if (lexer->c == '<')
			return (lexer_leftarrow(lexer));
		else if (lexer->c == '>')
			return (lexer_rightarrow(lexer));
		else if (lexer->c == ' ')
			lexer_isspace_skip(lexer);
		else if (ft_isprint(lexer->c))
			return (lexer_collect_id(lexer));
		else
			lexer_advance(lexer);
	}
	return ((void *)0);
}
