/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:39:01 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/19 20:39:24 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	if (!tableau)
		return ;
	else
	{
		while (tableau[i])
			free(tableau[i++]);
		free(tableau);
	}
}

void	delete_linked_list(t_tokenlist **token)
{
	t_tokenlist	*current;
	t_tokenlist	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		if (current && current->token && current->token->value)
			free(current->token->value);
		free(current->token);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_pipe(t_pipe **token)
{
	t_pipe	*current;
	t_pipe	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		free(current->path);
		free_tab(current->cmd);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_all(void)
{
	if (g_data.lexer)
		free(g_data.lexer);
	if (g_data.tokens)
		delete_linked_list(&g_data.tokens);
}
