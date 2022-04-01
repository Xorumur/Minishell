/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:25:11 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/01 22:17:11 by mlecherb         ###   ########.fr       */
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
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_tab(paths);
	return (NULL);
}

// int	get_redir(int token, t_tokenlist *token)
// {
// 	t_tokenlist	*tmp;

// 	tmp = token;
// 	if (token == 3)
// 		return (3);
// 	else if (token == 6)
// 		return (6);
// 	else if (token == 8)
// 		return (8);
// 	else if (token == 0)
// 		return (0);
// }

// char	*get_gilename(t_tokenlist *token)
// {
// 	t_tokenlist	*tmp;

// 	tmp = token;
// 	if (tmp->next)
// 		return (tmp->value);
// 	else
// 		return (NULL);
// }

// void	parsing(void)
// {
// 	t_tokenlist	*tmp;
// 	int			key;
// 	char		**cmd = NULL;
// 	int			i;
// 	int			redir;

// 	i = 2;
// 	key = 0;
// 	tmp = g_data.tokens;
// 	if (handle_error_token() == -1)
// 		return ;
// 	// penser a gerer le here doc
// 	if (tmp->next && tmp->next->next && tmp->token->e_type == 7)
// 		tmp = tmp->next->next;
// 	while (tmp != NULL)
// 	{
// 		redir = 0;
// 		while (tmp && tmp->token->e_type == 0)
// 		{
// 			if (key == 0)
// 			{
// 				cmd[0] = ft_strdup(search_path(tmp->token->value));
// 				cmd[1] = ft_strdup(tmp->token->value);
// 				search_path(tmp->token->value);
// 				tmp = tmp->next;
// 				key = -1;
// 			}
// 			else 
// 			{
// 				cmd[i++] = ft_strdup(tmp->token->value);
// 				tmp = tmp->next;
// 			}
// 		}
// 		key = 0;
// 		while (tmp && tmp->token->e_type != 0)
// 		{
// 			redir = get_redir(tmp->token->e_type, tmp);
// 			tmp = tmp->next;
// 		}
// 		ft_lstadd_back_pipe(g_data.pipe, ft_lstnew_pipe(cmd, redir, get_filename(tmp)));
// 		if (check_next_pipe)
// 	}
// }

char	**parser_cmd(t_tokenlist **token, char **cmd)
{
	int	i;

	i = 0;
	cmd = malloc(sizeof(char **) * 10);
	// printf("Here %i\n", i);
	while ((*token)->next != NULL && (*token)->token->e_type == 0)
	{
		// printf("Here b %i\n", i);
		cmd[i++] = ft_strdup((*token)->token->value);
		(*token) = (*token)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	boucle_redir(char	**cmd, t_tokenlist *token)
{
	while (token->token->e_type == 6)
	{
		ft_lstadd_back_pipe(&g_data.pipe,
					ft_lstnew_pipe(cmd, 6, token->next->token->value));
		token = token->next->next;
	}
	while (token->token->e_type == 8)
	{
		ft_lstadd_back_pipe(&g_data.pipe,
					ft_lstnew_pipe(cmd, 8, token->next->token->value));
		token = token->next->next;
	}
}

void	aff_pipe(t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = pipe;
	while (tmp)
	{
		printf("NODE : %i\n", i);
		printf("PATH %s\n", tmp->path);
		print_tab(pipe->cmd);
		if (pipe->is_pipe == 1)
			printf("PIPE\n");
		else if (pipe->is_redir == 1)
			printf("REDIR\n");
		tmp = tmp->next;
	}
}

void	parsing(void)
{
	t_tokenlist	*tmp;
	char		**cmd = NULL;
	int			redir;

	redir = 0;
	tmp = g_data.tokens;
	if (handle_error_token() == -1)
		return ;
	while (tmp != NULL)
	{
		cmd = parser_cmd(&tmp, cmd);
		print_tab(cmd);
		if (tmp->token->e_type == 6 || 
				tmp->token->e_type == 8)
		{
			redir = tmp->token->e_type;
			ft_lstadd_back_pipe(&g_data.pipe,
					ft_lstnew_pipe(cmd, redir, tmp->next->token->value));
			tmp = tmp->next->next;
			// boucle_redir(cmd, tmp);
		}
		else if (tmp->token->e_type == 3)
		{
			redir = 3;
			ft_lstadd_back_pipe(&g_data.pipe,
					ft_lstnew_pipe(cmd, redir, NULL));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	aff_pipe(g_data.pipe);
}