/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:55:21 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/22 13:50:37 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_echo(int *o, int *i, t_tokenlist **tmp, int redir)
{
	while (*i < ft_strlen("echo"))
		*i += 1;
	printf("%i\n", *i);
	if (!g_data.cmd[*i])
	{
		ft_putchar_fd('\n', redir);
		return (1);
	}
	while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
		*i += 1;
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	if (!ft_strncmp((*tmp)->token->value, "-n", ft_strlen("-n")))
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

void	folu(char *cmd, t_tokenlist **tmp, int redir, int *i)
{
	if ((*tmp))
		ft_putstr_fd((*tmp)->token->value, redir);
	(*tmp) = (*tmp)->next;
	*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1)
		*i += 1;
	*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
}

void	foli(char *cmd, int *i, t_tokenlist **tmp, int redir)
{
	if ((*tmp))
		ft_putstr_fd((*tmp)->token->value, redir);
	if ((*tmp) && (*tmp)->next)
		(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->token->e_type == 1)
	{
		ft_putstr_fd((*tmp)->token->value, redir);
		if ((*tmp))
			(*tmp) = (*tmp)->next;
		*i += 1;
		while (cmd[*i] && cmd[*i] == '=')
		{
			ft_putstr_fd((*tmp)->token->value, redir);
			(*tmp) = (*tmp)->next;
			*i += 1;
		}
	}
	while (cmd[*i] && ft_isprint(cmd[*i]) > 0 && ft_iswspace(cmd[*i]) != 1
		&& ft_isquote(cmd[*i]) != 1)
	{
		*i += 1;
	}
}

void	fole(char *cmd, int *i, int redir)
{
	ft_putchar_fd(' ', redir);
	*i += 1;
	while (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
		*i += 1;
}

void folo(t_tokenlist **tmp, int redir, int *o)
{
	while ((*tmp) && ft_isquote((*tmp)->token->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->token->value, redir);
		(*tmp) = (*tmp)->next;
	}
	if (*o == -1)
		ft_putchar_fd('\n', redir);
}