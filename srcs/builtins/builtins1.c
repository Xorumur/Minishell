/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:58:09 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/07 14:40:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pwd(void)
{
	char	pwd[1000];
	char	*res;

	res = getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}

int	change_cd(char	**directory)
{
	if (!directory[1])
		chdir(ft_getenv("HOME"));
	else if (chdir(directory[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(directory[1], STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	return (1);
}

int	cmd_echo(char **cmd)
{
	int	n;
	int	i;

	i = 1;
	n = 0;
	if (!cmd[1])
		n = 0;
	else if (!ft_strncmp(cmd[1], "-n", ft_strlen("-n")))
	{
		n = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}

int	cmd_export(char	*name, char *content)
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
	printf("Here export\n");
	return (1);
}

int	cmd_unset(char *name)
{
	t_env	*tmp;
	t_env	*del;

	tmp = g_data.env;
	if (name == NULL)
		return (1);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(name) + 1))
		{
			del = tmp;
			tmp->prev->next = tmp->next;
			free(del);
			return (1) ;
		}
		tmp = tmp->next;
	}
	return (1);
}