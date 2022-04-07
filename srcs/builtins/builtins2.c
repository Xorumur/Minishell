/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:22:36 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/06 13:59:42 by marvin           ###   ########.fr       */
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
	return (1);
}

int	cmd_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(1);
	return (1);
}
