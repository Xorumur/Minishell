/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:34:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/31 21:04:51 by epfennig         ###   ########.fr       */
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
	ioctl(ttyslot(), TIOCSETA, &conf);
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
		ft_putstr_fd("\n", STDOUT_FILENO);
		// if (g_data.status.is_fork == FALSE && g_data.status.is_dlredir == FALSE)
		// {
		// 	printf("\n");
		// 	rl_on_new_line();
		// 	rl_redisplay();
		// }
		// else if (g_data.status.is_fork == 1)
		// {
		// 	printf("\n");
		// 	rl_on_new_line();
		// }
		// else if (g_data.status.is_dlredir >= 0)
		// {
		// 	g_data.status.ctrlc = 1;
		// 	printf("\n");
		// 	rl_on_new_line();
		// 	rl_redisplay();
		// }
	}
}