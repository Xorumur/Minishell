/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:25:11 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/01 12:44:44 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*search_path(char *cmd)
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
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	free_tab(paths);
	return (NULL);
}

void	parsing(void)
{
	t_tokenlist	*tmp;
	int			key;

	key = 0;
	tmp = g_data.tokens;
	// penser a gerer le here doc
	if (tmp->token->e_type == 7)
		tmp = tmp->next->next;
	while (tmp != NULL)
	{
		while (tmp && tmp->token->e_type == 0)
		{
			if (key == 0)
			{
				search_path(tmp->token->value);
				tmp = tmp->next;
				key = -1;
			}
			else 
			{
				tmp = tmp->next;
			}
		}
		key = 0;
		while (tmp && tmp->token->e_type != 0)
			tmp = tmp->next;
	}
}