/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:58:09 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/04 22:38:34 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_pwd(void)
{
	char	pwd[1000];
	char	*res;

	res = getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	change_cd(char	*directory)
{
	if (!directory)
		chdir(ft_getenv("HOME"));
	else if (chdir(directory) == -1)
	{
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	}
	return ;
}

void	cmd_echo(char	*mess, char *option)
{
	ft_putstr_fd(mess, STDOUT_FILENO);
	if (!ft_strncmp(option, "-n", ft_strlen("-n")))
		write(1, "\n", STDOUT_FILENO);
	return ;
}

void	cmd_export(char	*name, char *content)
{
	if (name)
	{
		ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(name),
				ft_strdup(content)));
	}
	else
	{
		print_env(g_data.env, STDOUT_FILENO);
	}
}

void	cmd_unset(char *name)
{
	t_env	*tmp;
	t_env	*del;

	tmp = g_data.env;
	while (tmp)
	{
		if (ft_strncmp(name, g_data.env->name, ft_strlen(name)) == 0)
		{
			del = tmp;
			tmp->prev->next = tmp->next;
			free(del);
			return ;
		}
		tmp = tmp->next;
	}
}