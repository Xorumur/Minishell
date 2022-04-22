/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:55:21 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/22 17:18:25 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_echo(int *o, int *i, t_tokenlist **tmp, int redir)
{
	while (*i < ft_strlen("echo"))
		*i += 1;
	if (!g_data.cmd[*i])
	{
		ft_putchar_fd('\n', redir);
		return (1);
	}
	while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
		*i += 1;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	while (!ft_strncmp((*tmp)->token->value, "-n", ft_strlen("-n")))
	{
		(*tmp) = (*tmp)->next;
		*o = 1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) != 1)
			*i += 1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
			*i += 1;
	}
	return (0);
}

int	handle_quote(char *cmd, t_tokenlist **tmp, int *i, int redir)
{
	while ((*tmp) && ft_isquote((*tmp)->token->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->token->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	ft_putstr_fd((*tmp)->token->value, redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_isquote((*tmp)->token->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->token->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		else
			return (1);
	}
	return (0);
}

int	handle_string(char *cmd, t_tokenlist **tmp, int *i, int redir)
{
	ft_putstr_fd((*tmp)->token->value, redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}

void	handle_space(char *cmd, int *i, int redir)
{
	ft_putchar_fd(' ', redir);
	*i += 1;
	while (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
		*i += 1;
}

int	loop_echo(char *cmd, t_tokenlist **tmp, int *i, int redir)
{
	while (cmd[*i] && (*tmp) && (*tmp)->token->e_type != 5
		&& (*tmp)->token->e_type != 6 && (*tmp)->token->e_type != 8
		&& (*tmp)->token->e_type != 7)
	{
		if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		{
			if (handle_quote(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) != 1)
		{
			if (handle_string(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
			handle_space(cmd, i, redir);
	}
	return (0);
}
