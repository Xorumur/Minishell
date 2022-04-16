/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:58:09 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/16 10:04:37 by marvin           ###   ########.fr       */
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
	g_data.exec = 0;
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
	g_data.exec = 0;
	return (1);
}

