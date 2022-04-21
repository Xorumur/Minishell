/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:06:18 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 13:32:29 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**parser_cmd(t_tokenlist **token, char **cmd)
{
	int			i;
	t_tokenlist	*tmp;

	tmp = *token;
	i = 0;
	while (tmp != NULL && (tmp->token->e_type == 0
			|| tmp->token->e_type == 2 || tmp->token->e_type == 9))
	{
		i++;
		tmp = tmp->next;
	}	
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*token) != NULL && ((*token)->token->e_type == 0
			|| (*token)->token->e_type == 2 || (*token)->token->e_type == 9))
	{
		cmd[i++] = ft_strdup((*token)->token->value);
		(*token) = (*token)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	*get_map(int fd)
{
	char	buf[2];
	int		len;
	char	*line;

	len = read(fd, buf, 1);
	buf[1] = '\0';
	line = ft_strdup(buf);
	len = read(fd, buf, 1);
	buf[1] = '\0';
	while (len > 0)
	{
		line = ft_strjoin_w(line, buf);
		len = read(fd, buf, 1);
		buf[1] = '\0';
	}
	return (line);
	// free(line);
}

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