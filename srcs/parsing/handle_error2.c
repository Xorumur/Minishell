/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:44:13 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/04 21:44:13 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"\

int left_redirl_verif(t_tokenlist *tmp)
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