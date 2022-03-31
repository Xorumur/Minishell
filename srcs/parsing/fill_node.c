/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:45:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 20:54:32 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipe	*ft_lstnew_pipe(char *name, char *content)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_pipe(t_env **alst, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}