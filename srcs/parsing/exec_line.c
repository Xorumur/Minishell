/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:39:22 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/01 11:22:10 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**fill_tab(t_tokenlist **tmp, char **cmd)
{
	int	i;

	i = 0;
	while ((*tmp) && (*tmp)->token->e_type == 0)
	{
		cmd[i] = ft_strdup((*tmp)->token->value);
		// ft_putstr_fd(cmd[i], STDERR_FILENO);
		// ft_putstr_fd("\n", STDERR_FILENO);
		i++;
		(*tmp) = (*tmp)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	parser(t_tokenlist *tmp, int in)
{
	char		**cmd;
	int			fd[2];
	int			next_in;
	t_bool		is_pipe;

	is_pipe = FALSE;
	if (!tmp)
		return ;
	cmd = malloc(sizeof(char *) * 100);
	cmd = fill_tab(&tmp, cmd);
	// printf("pointer = %p\n", tmp);
	if (tmp && tmp->token->e_type == 3)
	{
		tmp = tmp->next;
		is_pipe = TRUE;
	}
	if (is_pipe)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(in, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			if (execve(cmd[0], cmd, g_data.tab_env) == -1)
			{
				write(STDERR_FILENO, "error: cannot execute ", 23);
				write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
				write(STDERR_FILENO, "\n", 1);
				exit(0);
			}
		}
		close(fd[1]);
		next_in = fd[0];
	}
	else
	{
		if (fork() == 0)
		{
			dup2(in, STDIN_FILENO);
			// if (tmp->token->e_type == 6)
			// 	dup2(open(tmp->next->token->value, O_WRONLY), STDOUT_FILENO);
			if (execve(cmd[0], cmd, g_data.tab_env) == -1)
			{
				write(2, "error: cannot execute ", 50);
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, "\n", 1);
				exit(0);
			}
		}
	}
	if (in != STDIN_FILENO)
		close(in);
	if (tmp != NULL)
		parser(tmp, next_in);
}

void	call_parser(void)
{
	t_tokenlist	*tmp;

	tmp = g_data.tokens;
	parser(tmp, STDIN_FILENO);
}
