/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_friendly2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:27:20 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 17:42:16 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	det_redir(t_tokenlist **tmp, int *redir)
{
	if ((*tmp) && ((*tmp)->token->e_type == 6 || (*tmp)->token->e_type == 8))
		(*redir) = verif_multiple_redir(tmp);
	return ;
}

int	*det_stdin(t_tokenlist **tmp, int *fd)
{
	if ((*tmp) && (*tmp)->token->e_type == 5)
	{
		pipe(fd);
		write_fd((*tmp)->next->token->value, fd[1]);
		close(fd[1]);
		(*tmp) = (*tmp)->next->next;
	}
	else if ((*tmp) && (*tmp)->token->e_type == 7)
	{
		pipe(fd);
		heredoc(tmp, fd[1]);
		close(fd[1]);
	}
	return (fd);
}
