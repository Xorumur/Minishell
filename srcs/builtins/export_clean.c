/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:46:28 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/20 12:46:28 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_same_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] != '\0')
		return (0);
	return (1);
}

int	ft_same_content(char *name, char *content)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(tmp->name)))
		{
			printf("crash\n");
			printf("Tmp->content %s\n", tmp->content);
			if (!ft_strncmp(content, tmp->content, ft_strlen(content)))
			{
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env_exist(char *name)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (ft_same_str(name, tmp->name) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_alloc_size(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1))
		i++;
	return (i + 1);
}

void	cmd_unset_assist(char *name, char *content)
{
	t_env	*env;
	t_env	*start;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	while (env)
	{
		if (ft_same_str(name, env->name) == 1)
		{
			free(env->content);
			env->content = NULL;
			env->content = ft_strdup(content);
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}

int	export_cmd(int redir)
{
	t_tokenlist	*tmp;
	int			i;
	char		*new_env;
	char		*content;

	content = NULL;
	new_env = NULL;
	i = 0;
	tmp = g_data.tokens;
	if (start_export(&tmp, &i, redir) == 0)
		return (0);
	if (normexport(content, new_env, tmp, i) == 1)
		return (1);
	g_data.exec = 0;
	return (1);
}
