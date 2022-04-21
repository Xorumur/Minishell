/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_friendly.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:00:00 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 22:45:06 by mlecherb         ###   ########.fr       */
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
	if (cmd && !ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
	{
		export_cmd(redir);
		if (cmd)
			free_tab(cmd);
		close(redir);
		return (1);
	}
	else if (cmd && !ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
	{
		echo_cmd(g_data, redir);
		if (cmd)
			free_tab(cmd);
		close(redir);
		g_data.exec = 0;
		return (1);
	}
	else if (cmd && !ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
	{
		cmd_unset(cmd);
		free_tab(cmd);
		g_data.exec = 0;
		return (1);
	}
	return (0);
}

void	get_cmd(char ***cmd, t_tokenlist **tmp)
{
	if ((*tmp)->token->e_type == 0 || (*tmp)->token->e_type == 2
		|| (*tmp)->token->e_type == 9)
	{
		if (*cmd)
			free_tab(*cmd);
		*cmd = parser_cmd(tmp, *cmd);
	}
}
