/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:34:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/04 18:24:38 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCGETA, &conf);
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_data.status.is_fork == FALSE && g_data.status.is_dlredir == FALSE) 
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (g_data.status.is_fork == TRUE)
		{
			printf("\n");
			rl_on_new_line();
		}
		else if (g_data.status.is_dlredir == TRUE)
		{
			g_data.status.ctrlc = 1;
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
	}
}