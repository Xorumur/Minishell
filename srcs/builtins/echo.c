/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:52:19 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 13:03:07 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	echo_cmd(t_data s_data, int redir)
{
	t_tokenlist	*tmp;
	char		*cmd;
	int			i;
	int			o;

	o = -1;
	i = 0;
	tmp = s_data.tokens;
	cmd = s_data.cmd;
	while (i < ft_strlen("echo"))
			i++;
	if (!cmd[i])
	{
		ft_putchar_fd('\n', redir);
		return (1);
	}
	while (cmd[i] && ft_iswspace(cmd[i]) == 1)
		i++;
	if (tmp->next)
		tmp = tmp->next;
	if (!ft_strncmp(tmp->token->value, "-n", ft_strlen("-n")))
	{
		tmp = tmp->next;
		o = 1;
		while (cmd[i] && ft_iswspace(cmd[i]) != 1)
			i++;
		while (cmd[i] && ft_iswspace(cmd[i]) == 1)
			i++;
	}
	while (cmd[i] && tmp && tmp->token->e_type != 5 && tmp->token->e_type != 6
		&& tmp->token->e_type != 8 && tmp->token->e_type != 7)
	{
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
		{
			if (tmp)
				ft_putstr_fd(tmp->token->value, redir);
			tmp = tmp->next;
			i++;
			while (cmd[i] && ft_isquote(cmd[i]) != 1)
				i++;
			i++;
			while (cmd[i] && ft_isquote(cmd[i]) == 1)
				i++;
		}
		else
		{
			if (tmp)
				ft_putstr_fd(tmp->token->value, redir);
			if (tmp && tmp->next)
				tmp = tmp->next;
			else
				tmp = NULL;
			while (cmd[i] && ft_isprint(cmd[i]) > 0 && ft_iswspace(cmd[i]) != 1
				&& ft_isquote(cmd[i]) != 1 && ft_isequal(cmd[i]) != 1)
			{
				i++;
			}
			if (cmd[i] && ft_isequal(cmd[i]) == 1)
				i++;
		}
		if (cmd[i] && ft_iswspace(cmd[i]) == 1)
		{
			ft_putchar_fd(' ', redir);
			i++;
			while (cmd[i] && ft_iswspace(cmd[i]) == 1)
				i++;
		}
	}
	while (tmp && ft_isquote(tmp->token->value[0]) == 1)
	{
		ft_putstr_fd(tmp->token->value, redir);
		tmp = tmp->next;
	}
	if (o == -1)
		ft_putchar_fd('\n', redir);
	g_data.exec = 0;
	return (1);
}
