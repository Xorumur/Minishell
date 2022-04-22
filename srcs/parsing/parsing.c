/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:43:48 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/21 19:02:28 by mlecherb         ###   ########.fr       */
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
	while (paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		filename = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(filename, X_OK))
			return (return_free(paths, filename));
		free(filename);
	}
	print_path_error(cmd, id);
	free_tab(paths);
	return (NULL);
}

char	**parser_cmd(t_tokenlist **token, char **cmd)
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

int	verif_multiple_redir(t_tokenlist **token)
{
	int	redir;

	redir = 0;
	while (*token && ((*token)->token->e_type == 6
			|| (*token)->token->e_type == 8))
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
	char	*tmp;
	int		id;

	if (exec_builtins(cmd, redir) == 1)
		return ;
	if (path_search(cmd) == 1)
		return ;
	g_data.status.is_fork = TRUE;
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
		close(redir);
	}
	waitpid(id, NULL, 0);
	g_data.exec = 0;
	return ;
}

void	parsing(void)
{
	t_tokenlist	*tmp;
	char		**cmd;
	int			redir;
	int			*fd;

	fd = malloc(sizeof(int) * 2);
	cmd = NULL;
	redir = -1;
	tmp = g_data.tokens;
	if (handle_error_token() == -1)
		return ;
	while (tmp != NULL)
	{
		get_cmd(&cmd, &tmp);
		det_redir(&tmp, &redir);
		fd = det_stdin(&tmp, fd);
		if (cmd && builtins_parsing(redir, cmd) == 1)
			return (free(fd));
		if (tmp)
			tmp = tmp->next;
	}
	if (cmd)
		exec(redir, cmd, fd[0]);
	free_in_pars(cmd, fd);
}
