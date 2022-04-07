/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:44:11 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/07 17:48:02 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_exist(char *name)
{
	t_env *tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen("name")))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}