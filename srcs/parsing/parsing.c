/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:43:48 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/19 20:44:14 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_path(char *cmd, int id)
{
	int		i;
	char	*tmp;
	char	*filename;
	char	**paths;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	tmp = ft_getenv("PATH");
	paths = ft_split(tmp, ':');
	free(tmp);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		filename = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(filename, X_OK))
		{
			free_tab(paths);
			return (filename);
		}
		i++;
		free(filename);
	}
	if (id == 0)
	{
		ft_putstr_fd("Minishell: ",STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	free_tab(paths);
	return (NULL);
}

char	**parser_cmd(t_tokenlist **token, char **cmd)
{
	int	i;
	t_tokenlist *tmp;

	tmp = *token;
	i = 0;
	while (tmp != NULL && (tmp->token->e_type == 0 ||
			tmp->token->e_type == 2 ||
			tmp->token->e_type == 9))
	{
		i++;
		tmp = tmp->next;
	}	
	cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*token) != NULL && ((*token)->token->e_type == 0 ||
			(*token)->token->e_type == 2 ||
			(*token)->token->e_type == 9))
	{
		cmd[i++] = ft_strdup((*token)->token->value);
		(*token) = (*token)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	verif_multiple_redir(t_tokenlist **token)
{
	int redir;

	redir = 0;
	while (*token && ((*token)->token->e_type == 6 ||
			(*token)->token->e_type == 8))
	{
		if ((*token)->token->e_type == 8)
		{
			redir = open((*token)->next->token->value,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (redir == -1)
				redir = open((*token)->next->token->value,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		}
		else if ((*token)->token->e_type == 6)
		{
			redir = open((*token)->next->token->value,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (redir == -1)
				redir = open((*token)->next->token->value,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);	
		}
		(*token) = (*token)->next->next;
	}
	return (redir);
}

void	exec(int redir, char **cmd, int in)
{
	int		id;
	char	*tmp;

	if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(1);
	}
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
		change_cd(cmd);
		return ;
	}
	if (builtins(cmd[0]) == 1)
	{
		if (in != -1)
			dup2(in, STDIN_FILENO);
		if (redir != -1 && redir != 24640)		
			dup2(redir, STDOUT_FILENO);
		is_builtins(cmd);
		return ;
	}
	tmp = search_path(cmd[0], 0);
	if (tmp == NULL)
	{
		g_data.exec = 127;
		free(tmp);
		return ;
	}
	g_data.status.is_fork = TRUE;
	free(tmp);
	id = fork();
	if (id == 0)
	{
		if (in != -1)
			dup2(in, STDIN_FILENO);
		if (redir != -1 && redir != 24640)
			dup2(redir, STDOUT_FILENO);
		tmp = search_path(cmd[0], 1);
		execve(tmp, cmd, get_new_env());
		free(tmp);
		close(in);
		if (redir)
			close(redir);
		exit(1);
	}
	g_data.exec = 0;
	waitpid(id, NULL, 0);
	return ;
}

void	parsing(void)
{
	t_tokenlist	*tmp;
	char		**cmd = NULL;
	int			redir;
	int			fd[2];
	
	fd[0] = 0;
	fd[1] = 0;
	redir = -1;
	tmp = g_data.tokens;
	if (handle_error_token() == -1)
		return ;
	while (tmp != NULL)
	{
		if (tmp->token->e_type == 0 || tmp->token->e_type == 2 || tmp->token->e_type == 9) 
		{
			if (cmd)
				free_tab(cmd);
			cmd = parser_cmd(&tmp, cmd);
		}
		if (tmp && (tmp->token->e_type == 6 ||
				tmp->token->e_type == 8))
		{
			redir = verif_multiple_redir(&tmp);	
		}
		else if (tmp && tmp->token->e_type == 5)
		{
			pipe(fd);
			write_fd(tmp->next->token->value, fd[1]);
			close(fd[1]);
			tmp = tmp->next->next;
		}
		else if (tmp && tmp->token->e_type == 7)
		{
			pipe(fd);
			heredoc(&tmp, fd[1]);
			close(fd[1]);
		}
		else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		{
			export_cmd();
			free_tab(cmd);
			return ;
		}
		else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		{
			echo_cmd();
			free_tab(cmd);
			return ;
		}
		else if (tmp)
			tmp = tmp->next;
	}
	if (cmd)
	{
		exec(redir, cmd, fd[0]);
		free_tab(cmd);
	}
}
