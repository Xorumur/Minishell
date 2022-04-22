/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_friendly2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:27:20 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 22:45:20 by mlecherb         ###   ########.fr       */
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

void	double_free_str(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return ;
}

int	helper_parser(char *line, char *temp)
{
	if (temp[0] == 0)
	{
		if (!line)
			line = ft_strdup("\n");
		else
			line = ft_strjoin_h(line, ft_strdup("\n"));
		free(temp);
	}
	return (0);
}

int	unset_norm(t_env **tmp, char *cmd)
{
	if (!ft_strncmp(cmd, (*tmp)->name, ft_strlen(cmd)))
	{
		double_free_str((*tmp)->name, (*tmp)->content);
		(*tmp) = (*tmp)->next;
		free((*tmp)->prev);
		(*tmp)->prev = NULL;
		return (1);
	}
	else if (!ft_strncmp(cmd, g_data.env->name, ft_strlen(cmd)))
	{
		double_free_str(g_data.env->name, g_data.env->content);
		if (g_data.env->next)
		{
			g_data.env->prev->next = g_data.env->next;
			g_data.env->next->prev = g_data.env->prev;
		}
		else
			g_data.env->prev->next = NULL;
		free(g_data.env);
		return (1);
	}
	return (0);
}
