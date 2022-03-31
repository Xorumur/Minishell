/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:28:31 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 18:11:01 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data_env(char **env)
{
	int		i;
	char	**tableau;

	i = 0;
	tableau = ft_split(env[i++], '=');
	g_data.env = ft_lstnew_env(ft_strdup(tableau[0]), ft_strdup(tableau[1]));
	free_tab(tableau);
	while (env[i])
	{
		tableau = ft_split(env[i], '=');
		ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(tableau[0]),
				ft_strdup(tableau[1])));
		free_tab(tableau);
		i++;
	}
}

void	print_env(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x " , fd);
		ft_putstr_fd(tmp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(tmp->content, fd);
		ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->next;
	}
}

char	*ft_getenv(char *name)
{
	t_env	*tmp;
	char	*content;

	content = NULL;
	tmp = g_data.env;
	while (g_data.env)
	{
		if (!ft_strncmp(name, g_data.env->name, ft_strlen(g_data.env->name) + 1))
		{
			if (g_data.env->content)
				content = ft_strdup(g_data.env->content);
			else
				content = NULL;
			break ;
		}
		g_data.env = g_data.env->next;
	}
	g_data.env = tmp;
	return (content);
}