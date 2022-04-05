/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:55:31 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/05 11:05:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_verif(void)
{
	printf("syntax error near unexpected token '|'\n");
	g_data.verif = TRUE;
	return(-1);

}

int	redir_verif(t_tokenlist *tmp)
{
	t_tokenlist *lst;

	lst = tmp;
	if (tmp && lst->next && lst->next->token->e_type != 0)
	{
		printf("syntax error near unexpected token '%s'\n", tmp->next->token->value);
		g_data.verif = TRUE;
		return(-1);
	}
	else if (tmp->next == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
		g_data.verif = TRUE;
		return (-1);
	}
	else
	{
		g_data.verif = TRUE;	
		return (0);
	}
}

int	dredir_verif(t_tokenlist *tmp)
{
	t_tokenlist *lst;

	lst = tmp;
	if (!tmp->next)
	{
		printf("syntax error near unexpected token 'newline'\n");
		g_data.verif = TRUE;
		return (-1);
	}
	else if (lst->next && lst->next->token->e_type != 0)
	{
		printf("syntax error near unexpected token '%s'\n", tmp->next->token->value);
		g_data.verif = TRUE;
		return(-1);
	}
	else
	{
		g_data.verif = FALSE;
		return (0);
	}
}

int	dredirl_verif(t_tokenlist *tmp)
{
	t_tokenlist *lst;

	lst = tmp;
	if (!lst->prev)
	{
		printf("syntax error near unexpected token `newline'\n");
		g_data.verif = TRUE;
		return (-1);
	}
	else if (lst->next == NULL)
	{
		printf("syntax error near unexpected token `newline'\n");
		g_data.verif = TRUE;
		return (-1);
	}
	else
	{
		g_data.verif = FALSE;
		return (0);
	}
}

int	handle_error_token(void)
{
	t_tokenlist	*tmp;
	int			r;

	r = 0;
	tmp = g_data.tokens;
	while (tmp)
	{
		if (tmp->token->e_type == 3)
			r = pipe_verif();
		else if (tmp->token->e_type == 6)
			r = redir_verif(tmp);
		else if (tmp->token->e_type == 8)
			r = dredir_verif(tmp);
		else if (tmp->token->e_type == 7)
			r = dredirl_verif(tmp);
		else if (tmp->token->e_type == 5)
			r =	left_redirl_verif(tmp);
		if (r == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (r);
}