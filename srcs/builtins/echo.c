/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:52:19 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/19 19:42:10 by mlecherb         ###   ########.fr       */
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

int	echo_cmd(void)
{
	t_tokenlist	*tmp;
	char		*cmd;
	int			i;
	int			o;
	// char		*line;

	// line = NULL;
	o = -1;
	i = 0;
	tmp = g_data.tokens;
	cmd = g_data.cmd;
	while (i < ft_strlen("echo"))
		i++;
	if (!cmd[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
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
	// printf("line %s\n", cmd + i);
	// printf("value : %s | type : %i \n", tmp->token->value, tmp->token->e_type);
	// if (tmp->next)
	// 	printf("value : %s | type : %i \n", tmp->next->token->value, tmp->next->token->e_type);
	while (cmd[i] && tmp && tmp->token->e_type != 5 && tmp->token->e_type != 6 &&
			tmp->token->e_type != 8 && tmp->token->e_type != 7)
	{
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
		{
			if (tmp)
				ft_putstr_fd(tmp->token->value, STDOUT_FILENO);
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
				ft_putstr_fd(tmp->token->value, STDOUT_FILENO);
			if (tmp && tmp->next)
				tmp = tmp->next;
			else 
				tmp = NULL;
			while (cmd[i] && ft_isprint(cmd[i]) > 0 &&
					ft_iswspace(cmd[i]) != 1 &&
						ft_isquote(cmd[i]) !=  1 &&
						ft_isequal(cmd[i]) != 1)
			{
				i++;
			}
			if (cmd[i] && ft_isequal(cmd[i]) == 1)
				i++;
		}
		if (cmd[i] && ft_iswspace(cmd[i]) == 1)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
			while (cmd[i] && ft_iswspace(cmd[i]) == 1)
				i++;
		}
	}
	if (o == -1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_data.exec = 0;
	return (1);
}