/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:22:36 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 22:44:26 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_env(void)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
	g_data.exec = 0;
	return (1);
}

int	cmd_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	g_data.exec = 0;
	exit(1);
	return (1);
}

int	cmd_unset(char **cmd)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = g_data.env;
	if (!cmd[1])
		return (1);
	while (cmd[i])
	{
		printf("unset arg : %s\n", cmd[i]);
		while (g_data.env)
		{
			if (unset_norm(&tmp, cmd[i]) == 1)
				break ;
			g_data.env = g_data.env->next;
		}
		g_data.env = tmp;
		i++;
	}
	g_data.exec = 0;
	return (1);
}
