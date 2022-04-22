/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:47:43 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 23:53:57 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_content(char **new_env, int *i, t_tokenlist **tmp, char *cmd)
{
	while (ft_iswspace(cmd[*i]))
		*i += 1;
	if (*i == ft_strlen(g_data.cmd))
		return (-1);
	if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 2;
	*new_env = ft_strdup((*tmp)->token->value);
	*i += ft_strlen(*new_env);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	return (0);
}

void	change_env(char *new_env, char *content)
{
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

int	freee(char *s1)
{
	if (s1)
		free(s1);
	return (1);
}

int	start_export(t_tokenlist **tmp, int *i, int redir)
{
	if (redir == -1)
		redir = 1;
	while (*i < ft_strlen("export"))
		*i += 1;
	if (!(*tmp)->next || (*tmp)->next->token->e_type == 6
		|| (*tmp)->next->token->e_type == 8)
	{
		print_env(g_data.env, redir);
		g_data.exec = 0;
		return (0);
	}
	(*tmp) = (*tmp)->next;
	return (1);
}

void	elif(char *cmd, int *i, t_tokenlist **tmp, char **content)
{
	*i += 1;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	while (cmd[*i] && cmd[*i] == '=' && (*tmp) && (*tmp)->token->e_type == 1)
	{
		if (!*content)
			*content = ft_strdup((*tmp)->token->value);
		else
			*content = ft_strjoin_w(*content, (*tmp)->token->value);
		*i += 1;
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	return ;
}
