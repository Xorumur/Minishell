/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:06:18 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 16:37:34 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_fd_echo(int reada, int fd)
{
	char	buf[2];
	int		len;
	char	*line;
	// int		read;

	// read = open(path, O_RDONLY);
	// if (read == -1)
	// {
	// 	ft_putstr_fd(path, STDERR_FILENO);
	// 	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	// 	return ;
	// }
	len = read(reada, buf, 1);
	buf[1] = '\0';
	line = ft_strdup(buf);
	while (len > 0)
	{
		line = ft_strjoin_w(line, buf);
		len = read(reada, buf, 1);
		buf[1] = '\0';
	}
	ft_putstr_fd(line, fd);
	free(line);
	close(reada);
}

void	handle_echo(int redir)
{
	int	id;
	t_tokenlist	*tmp;
	char	**cmd;
	int		fd[2];
	t_data	s_data;

	s_data = g_data;
	cmd = NULL;
	cmd = parser_cmd(&tmp, cmd);
	if (tmp && (tmp->token->e_type == 6 || tmp->token->e_type == 8))
		redir = verif_multiple_redir(&tmp);
	free_tab(cmd);
	id = fork();
	if (id == 0)
	{
		if (pipe(fd) == -1)
			exit(1);
		echo_cmd(s_data, fd[1]);
		write_fd_echo(fd[0], redir);
		exit(1);
	}
	else
	{
		close(redir);
		waitpid(id, NULL, 0);
	}
	return ;
}