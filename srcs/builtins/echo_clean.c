/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:28:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/22 17:21:22 by mlecherb         ###   ########.fr       */
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
	if (skip_echo(&o, &i, &tmp, redir) != 1)
	{
		if (loop_echo(cmd, &tmp, &i, redir) == 1)
			;
	}
	if (o == -1)
		ft_putchar_fd('\n', redir);
	g_data.exec = 0;
	return (1);
}
