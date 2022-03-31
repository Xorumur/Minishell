/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:34:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 14:37:13 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}
