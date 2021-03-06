/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:43:58 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/20 11:43:58 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	left_redirl_verif(t_tokenlist *tmp)
{
	t_tokenlist	*lst;

	lst = tmp;
	if (!tmp->next)
	{
		printf("syntax error near unexpected token 'newline'\n");
		g_data.verif = TRUE;
		g_data.exec = 258;
		return (-1);
	}
	else if (lst->next && lst->next->token->e_type != 0)
	{
		printf("syntax error near unexpected token '%s'\n",
			tmp->next->token->value);
		g_data.verif = TRUE;
		g_data.exec = 258;
		return (-1);
	}
	else
	{
		g_data.verif = FALSE;
		return (0);
	}
}

int	checker_arg(t_tokenlist *lst)
{
	t_tokenlist	*tmp;
	int			count;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->token->e_type == 0 || tmp->token->e_type == 2
			|| tmp->token->e_type == 9)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
