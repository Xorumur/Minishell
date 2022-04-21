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

static void	cmd_unset_assist(char *name, char *content)
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
	char		*cmd;
	int			i;
	char		*new_env;
	char		*content;

	content = NULL;
	i = 0;
	cmd = g_data.cmd;
	tmp = g_data.tokens;
	while (i < ft_strlen("export"))
		i++;
	if (!tmp->next || tmp->next->token->e_type == 6 || tmp->next->token->e_type == 8)
	{
		print_env(g_data.env, redir);
		g_data.exec = 0;
		return (1);
	}
	tmp = tmp->next;
	while (cmd[i])
	{
		content = NULL;
		new_env = NULL;
		while (ft_iswspace(cmd[i]))
			i++;
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
			i += 2;
		new_env = ft_strdup(tmp->token->value);
		i += ft_strlen(new_env);
		// printf("New env : %s\n", new_env);
		if (tmp->next)
			tmp = tmp->next;
		if (!cmd[i])
		{
			if (new_env)
				free(new_env);
			return (1);
		}
		else if (cmd[i] && tmp && ft_iswspace(cmd[i]) == 1)
		{
			if (new_env)
				free(new_env);
			continue ;
		}
		else if (cmd[i] && tmp && tmp->token->e_type == 1)
		{
			i++;
			if (tmp->next)
				tmp = tmp->next;
			while (cmd[i] && tmp && tmp->token->e_type == 1)
			{
				if (!content)
					content = ft_strdup(tmp->token->value);
				else
					content = ft_strjoin_w(content, tmp->token->value);
				i++;
				if (tmp->next)
					tmp = tmp->next;
			}
		}
		if (tmp && tmp->token->value[0] == 0)
		{
			while (cmd[i] && ft_iswspace(cmd[i]) != 1)
				i++;
			if (tmp->next)
				tmp = tmp->next;
		}
		else if (cmd[i] && ft_isquote(cmd[i]) == 1)
		{
			if (!content)
				content = ft_strdup(tmp->token->value);
			else
				content = ft_strjoin_w(content, tmp->token->value);
			if (tmp->next)
				tmp = tmp->next;
			i++;
			while (cmd[i] && ft_isquote(cmd[i]) != 1)
				i++;
			if (cmd[i] != '\0')
				i++;
		}
		else if (cmd[i] && ft_iswspace(cmd[i]) != 1)
		{
			if (!content)
				content = ft_strdup(tmp->token->value);
			else
				content = ft_strjoin_w(content, tmp->token->value);
			if (tmp->next)
				tmp = tmp->next;
			i += ft_strlen(content);
		}
		if (env_exist(new_env) == 0)
			ft_lstadd_back_env(&g_data.env,
				ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
		else if (ft_same_content(new_env, content) != 1)
			cmd_unset_assist(new_env, content);
		if (new_env)
			free(new_env);
		if (content)
			free(content);
	}
	g_data.exec = 0;
	return (1);
}
