/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing2.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mlecherb <mlecherb@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/19 20:44:32 by mlecherb		  #+#	#+#			 */
/*   Updated: 2022/04/19 20:44:32 by mlecherb		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verif_limiter(char *s1, char *limiter)
{
	int	i;

	i = 0;
	while (s1[i] == limiter[i])
	{
		if (s1[i] == '\0' && limiter[i] == '\0')
			return (1);
		i++;
	}
	return (-1);
}

void	heredoc(t_tokenlist **token, int in)
{
	char	*line;
	char	*temp;

	line = NULL;
	while (1)
	{
		temp = readline("> ");
		if (!temp)
			return ;
		else if (temp[0] != 0)
		{
			if (verif_limiter(temp, (*token)->next->token->value) == 1)
			{
				ft_putstr_fd(line, in);
				free(line);
				free(temp);
				(*token) = (*token)->next->next;
				return ;
			}
			if (line)
				temp = ft_strjoin_h(line, temp);
			line = ft_strjoin(temp, "\n");
			free(temp);
		}
		else if (temp[0] == 0)
		{
			if (!line)
				line = ft_strdup("\n");
			else
				line = ft_strjoin_h(line, ft_strdup("\n"));
			free(temp);
		}
	}
}

void	write_fd(char *path, int fd)
{
	char	buf[2];
	int		len;
	char	*line;
	int		fdin;

	fdin = open(path, O_RDONLY);
	if (fdin == -1)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	len = read(fdin, buf, 1);
	buf[1] = '\0';
	line = ft_strdup(buf);
	while (len > 0)
	{
		line = ft_strjoin_w(line, buf);
		len = read(fdin, buf, 1);
		buf[1] = '\0';
	}
	ft_putstr_fd(line, fd);
	free(line);
	close(fdin);
}

int	builtins(char *cmd)
{
	int	retour;

	retour = 0;
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		retour = 1;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		retour = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		retour = 1;
	return (retour);
}

int	is_builtins(char **cmd)
{
	int	retour;

	retour = 0;
	if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		retour = cmd_unset(cmd);
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		retour = change_cd(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		retour = get_pwd();
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		retour = cmd_env();
	return (retour);
}
