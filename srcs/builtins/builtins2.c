/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:22:36 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 15:47:31 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_env(int fd)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->content, fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->next;
	}
}

void	cmd_exit(int fd)
{
	ft_putstr_fd("exit\n", fd);
	exit(1);
}