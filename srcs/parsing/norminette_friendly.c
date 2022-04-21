/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_friendly.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:00:00 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 15:15:53 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_path_error(char *cmd, int id)
{
	if (id == 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return ;
}

char	*return_free(char **free, char *to_return)
{
	free_tab(free);
	return (to_return);
}

int	builtins_parsing(int redir, char **cmd)
{
	if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
	{
		export_cmd(redir);
		free_tab(cmd);
		close(redir);
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
	{
		echo_cmd(g_data, redir);
		free_tab(cmd);
		close(redir);
		g_data.exec = 0;
		return (1);
	}
	return (0);
}
