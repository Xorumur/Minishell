/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:25:11 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/04 23:36:24 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_path(char *cmd)
{
	int		i;
	char	*tmp;
	char	*filename;
	char	**paths;

	if (!access(cmd, X_OK))
			return (cmd);
	tmp = ft_getenv("PATH");
	paths = ft_split(tmp, ':'); //parsing_paths(cmd);
	free(tmp);
	// print_tab(paths);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		filename = ft_strjoin(tmp, cmd);
		// printf("%s\n", filename);
		free(tmp);
		if (!access(filename, X_OK))
		{
			free_tab(paths);
			return (filename);
		}
		i++;
		free(filename);
	}
	ft_putstr_fd("Minishell: ",STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_tab(paths);
	return (NULL);
}

char	**parser_cmd(t_tokenlist **token, char **cmd)
{
	int	i;

	i = 0;
	cmd = malloc(sizeof(char **) * 10);
	// printf("Here %i\n", i);
	while ((*token) != NULL && ((*token)->token->e_type == 0 ||
			(*token)->token->e_type == 2 ||
			(*token)->token->e_type == 9))
	{
		// printf("Here b %i\n", i);
		cmd[i++] = ft_strdup((*token)->token->value);
		(*token) = (*token)->next;
		// printf("A\n");
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
	int	id;
	
	// printf("in = %i | redir = %i\n", in, redir);
	// printf("ici\n");
	// print_tab(cmd);
	g_data.status.is_fork = TRUE;
	id = fork();
	if (id == 0)
	{
		// printf("in = %i | redir = %i\n", in, redir);
		if (in != -1)
			dup2(in, STDIN_FILENO);
		if (redir != -1 && redir != 24640)
			dup2(redir, STDOUT_FILENO);
		if (search_path(cmd[0]) == NULL)
			exit(1);
		// if (is_builtins(cmd[0]) == 1)
		// 	return ;
		execve(search_path(cmd[0]), cmd, get_new_env());
		close(in);
	}
	waitpid(id, NULL, 0);
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
	// printf("in = %i | redir = %i\n", fd[0], redir);
	if (handle_error_token() == -1)
		return ;
	while (tmp != NULL)
	{
		if (tmp->token->e_type == 0 || tmp->token->e_type == 2 || tmp->token->e_type == 9) 
			cmd = parser_cmd(&tmp, cmd);
		// printf("token : %i | value : %s\n", tmp->token->e_type, tmp->token->value);
		if (tmp && (tmp->token->e_type == 6 ||
				tmp->token->e_type == 8))
		{
			redir = verif_multiple_redir(&tmp);	
		}
		else if (tmp && tmp->token->e_type == 5)
		{
			fd[0] = open(tmp->next->token->value, O_RDONLY);
			write_fd(fd[0]);
			tmp = tmp->next->next;
		}
		else if (tmp && tmp->token->e_type == 7)
		{
			pipe(fd);
			heredoc(&tmp, fd[1]);
			close(fd[1]);
		}
	}
	exec(redir, cmd, fd[0]);
	free_tab(cmd);
}