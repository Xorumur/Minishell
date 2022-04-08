/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:29:02 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/08 15:44:29 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	echo_cmd(void)
{
	t_tokenlist	*tmp;
	char		*cmd;
	int			i;
	int			o;
	char		*line;

	line = NULL;
	o = -1;
	i = 0;
	tmp = g_data.tokens;
	cmd = g_data.cmd;
	while (i < ft_strlen("echo"))
		i++;
	while (cmd[i] && ft_iswspace(cmd[i]) == 1)
		i++;
	tmp = tmp->next;
	if (!ft_strncmp(tmp->token->value, "-n", ft_strlen("-n")))
	{
		tmp = tmp->next;
		o = 1;
		while (ft_iswspace(cmd[i]) != 1)
			i++;
		while (ft_iswspace(cmd[i]) == 1)
			i++;
	}
	// printf("line %s\n", cmd + i);
	// printf("value : %s | type : %i \n", tmp->token->value, tmp->token->e_type);
	// printf("value : %s | type : %i \n", tmp->next->token->value, tmp->next->token->e_type);
	while (cmd[i])
	{
		// printf("\nline %s\n", cmd + i);
		while (cmd[i] && ft_isprint(cmd[i]) > 0 && ft_iswspace(cmd[i]) != 1 && ft_isquote(cmd[i]) != 1)
			i++;
		// if (ft_isquote(cmd[i]) != 1)
			ft_putstr_fd(tmp->token->value, STDOUT_FILENO);
		if (tmp->next)
			tmp = tmp->next;
		while (cmd[i] && ft_iswspace(cmd[i]) == 1)
		{
			ft_putchar_fd(cmd[i], STDOUT_FILENO);
			while (cmd[i] && ft_iswspace(cmd[i]) == 1)
				i++;
		}
		if (cmd[i] && ft_isquote(cmd[i]) == 1 && tmp->next)
		{
			ft_putstr_fd(tmp->token->value, STDOUT_FILENO);
			if (tmp->next)
				tmp = tmp->next;
			i++;
			while (cmd[i] && ft_isquote(cmd[i]) != 1)
				i++;
			// printf("line %s\n", cmd + i);
		}
		if (cmd[i] && cmd[i] == '\0')
			break ;
		else
			i++;
		// printf("line %s\n", cmd + i);
	}
	if (o == -1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}