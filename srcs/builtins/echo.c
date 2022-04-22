/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:52:19 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/22 13:50:14 by mlecherb         ###   ########.fr       */
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
	printf("%s\n", cmd);
	if (redir == -1)
		redir = 1;
	if (skip_echo(&o, &i, &tmp, redir) == 1)
		return (1);
	while (cmd[i] && tmp && tmp->token->e_type != 5 && tmp->token->e_type != 6
		&& tmp->token->e_type != 8 && tmp->token->e_type != 7)
	{
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
			folu(cmd, &tmp, redir, &i);
		else
			foli(cmd, &i, &tmp, redir);
		if (cmd[i] && ft_iswspace(cmd[i]) == 1)
			fole(cmd, &i, redir);
	}
	folo(&tmp, redir, &o);
	g_data.exec = 0;
	return (1);
}
