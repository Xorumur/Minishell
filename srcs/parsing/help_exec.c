/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:24:13 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 14:54:46 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void process_fork_builtins(char **cmd, int redir)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (redir != -1)
			dup2(redir, STDOUT_FILENO);
		is_builtins(cmd);
		close(redir);
		exit(1);
	}
	waitpid(id, NULL, 0);
	return ;
}

int	exec_builtins(char **cmd, int redir)
{
	if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(1);
	}
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
		change_cd(cmd);
		return (1);
	}
	if (builtins(cmd[0]) == 1)
	{
		process_fork_builtins(cmd, redir);
		return (1);
	}
	return (0);
}

int	path_search(char **cmd)
{
	char	*tmp;

	tmp = search_path(cmd[0], 0);
	if (tmp == NULL)
	{
		g_data.exec = 127;
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
