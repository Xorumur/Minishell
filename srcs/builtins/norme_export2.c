/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:25:29 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 23:46:37 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	elef(char *cmd, t_tokenlist **tmp, int *i)
{
	while (cmd[*i] && ft_iswspace(cmd[*i]) != 1)
		i += 1;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
}

void	elaf(char *cmd, t_tokenlist **tmp, int *i, char **content)
{
	if (!*content)
		*content = ft_strdup((*tmp)->token->value);
	else
		*content = ft_strjoin_w(*content, (*tmp)->token->value);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1)
		*i += 1;
	if (cmd[*i] != '\0')
		*i += 1;
}

void	elof(char **content, t_tokenlist **tmp, int *i)
{
	if (!*content)
		*content = ft_strdup((*tmp)->token->value);
	else
		*content = ft_strjoin_w(*content, (*tmp)->token->value);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	*i += ft_strlen(*content);
}

int	normexport(char *content, char *new_env, t_tokenlist *tmp, int i)
{
	while (g_data.cmd[i])
	{
		content = NULL;
		new_env = NULL;
		if (skip_content(&new_env, &i, &tmp, g_data.cmd) == -1)
			return (1);
		if (!g_data.cmd[i])
			return (freee(new_env));
		else if (g_data.cmd[i] && tmp && ft_iswspace(g_data.cmd[i]) == 1)
		{
			freee(new_env);
			continue ;
		}
		else if (g_data.cmd[i] && tmp && tmp->token->e_type == 1)
			elif(g_data.cmd, &i, &tmp, &content);
		if (tmp && tmp->token->value[0] == 0)
			elef(g_data.cmd, &tmp, &i);
		else if (g_data.cmd[i] && ft_isquote(g_data.cmd[i]) == 1)
			elaf(g_data.cmd, &tmp, &i, &content);
		else if (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
			elof(&content, &tmp, &i);
		change_env(new_env, content);
	}
	g_data.exec = 0;
	return (1);
}
