/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:58:09 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 16:58:36 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_pwd(int fd)
{
	char	pwd[1000];
	char	*res;

	res = getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(res, fd);
	ft_putchar_fd('\n', fd);
}

void	change_cd(char	*directory)
{
	if (!directory)
		chdir(ft_getenv("HOME"));
	else if (chdir(directory) == -1)
	{
		ft_putstr_fd(directory, 1);
		ft_putchar_fd(':', 1);
		ft_putstr_fd("No such file or directory\n", 1);
	}
	return ;
}

void	cmd_echo(char	*mess, int option, int fd)
{
	ft_putstr_fd(mess, fd);
	if (option == 1)
		write(1, "\n", fd);
	return ;
}

void	cmd_export(char	*name, char *content, int fd)
{
	if (name)
	{
		ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(name),
				ft_strdup(content)));
	}
	else
	{
		print_env(g_data.env, fd);
	}
}

void	cmd_unset(char *name)
{
	t_env	*tmp;
	t_env	*del;

	tmp = g_data.env;
	while (tmp)
	{
		if (tmp->name == name)
		{
			del = tmp;
			tmp->prev->next = tmp->next;
			free(del);
			return ;
		}
		tmp = tmp->next;
	}
}