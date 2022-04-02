/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:45:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/02 13:57:13 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipe	*ft_lstnew_pipe(char **cmd, int next_token, char *file)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (new == NULL)
		return (NULL);
	new->path = ft_strdup(search_path(cmd[0]));
	print_tab(&cmd[1]);
	printf("size : %i\n", tab_size(&cmd[1]));
	printf("token : %i\n", next_token);
	new->cmd = realloc_tab(&cmd[1], tab_size(&cmd[1]) + 1);
	new->file = ft_strdup(file);
	if (next_token == 6)
	{
		new->is_redir = TRUE;
		new->fd_redir = open(file, O_CREAT | O_WRONLY | O_TRUNC,
							0644);
	}
	else if (next_token == 3)
	{
		new->is_pipe = TRUE;
		pipe(new->fd);
	}
	else if (next_token == 8)
	{
		new->is_redir = TRUE;
		new->fd_redir = open(file, O_CREAT | O_WRONLY | O_APPEND,
							0644);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_pipe(t_pipe **alst, t_pipe *new)
{
	t_pipe	*temp;

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