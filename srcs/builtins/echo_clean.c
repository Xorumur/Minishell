/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:28:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/22 15:09:39 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_clean(t_data s_data, int redir)
{
	t_tokenlist	*tmp;
	char		*cmd;
	int			i;
	int			o;

	o = -1;
	i = 0;
	tmp = s_data.tokens;
	cmd = s_data.cmd;
	if (redir == -1)
		redir = 1;
	if (skip_echo(&o, &i, &tmp, redir) == 1)
		return (1);
	while (cmd[i] && tmp && tmp->token->e_type != 5 && tmp->token->e_type != 6
		&& tmp->token->e_type != 8 && tmp->token->e_type != 7)
	{
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
		{
			while (tmp && ft_isquote(tmp->token->value[0]) == 1)
			{
				ft_putstr_fd(tmp->token->value, redir);
				if (tmp->next)
					tmp = tmp->next;
			}
			while (cmd[i] && ft_isquote(cmd[i]) == 1)
				i++;
			while (cmd[i] && ft_isquote(cmd[i]) != 1)
				i++;
			while (cmd[i] && ft_isquote(cmd[i]) == 1)
				i++;
			ft_putstr_fd(tmp->token->value, redir);
			if (tmp->next)
				tmp = tmp->next;
			while (tmp && ft_isquote(tmp->token->value[0]) == 1)
			{
				ft_putstr_fd(tmp->token->value, redir);
				if (tmp->next)
					tmp = tmp->next;
				else
					return (1);
			}
			// continue ;
		}
		else if (cmd[i] && ft_iswspace(cmd[i]) != 1)
		{
			ft_putstr_fd(tmp->token->value, redir);
			if (tmp->next)
				tmp = tmp->next;
			else
				return (1);
			while (cmd[i] && ft_isquote(cmd[i]) != 1 && ft_iswspace(cmd[i]) != 1 && ft_isprint(cmd[i]) > 1 && cmd[i] != '=')
				i++;
			// printf("\n LIGNE : %s\n", cmd + i);
			printf("char ici%c\n", cmd[i]);
			// continue ;
		}
		else if (cmd[i] && ft_iswspace(cmd[i]) == 1)
		{
			ft_putchar_fd(' ', redir);
			i += 1;
			while (cmd[i] && ft_iswspace(cmd[i]) == 1)
				i += 1;
			// printf("Passage\n");
			// continue ;
		}
	}
	if (o != 1)
		ft_putchar_fd('\n', redir);
	g_data.exec = 0;
	return (1);
}