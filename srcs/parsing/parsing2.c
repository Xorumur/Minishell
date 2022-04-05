#include "../../includes/minishell.h"

int		verif_limiter(char *s1, char *limiter)
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
    int     i;
	char	*temp;

    i = 0;
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
				(*token) = (*token)->next->next;
				return ;
			}
			if (!line)
				line = ft_strdup(temp);
			else
				line = ft_strjoin(line, temp);
			free(temp);
			line = ft_strjoin(line, "\n");
		}
    }
}

void	write_fd(int fd)
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
		line = ft_strjoin(line, buf);
		len = read(fd, buf, 1);
		buf[1] = '\0';
	}
	ft_putstr_fd(line, fd);
	free(line);
}

// int	is_builtins(char **cmd)
// {
// 	if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
// 		cmd_unset(cmd[1]);
// 	else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
// 		cmd_export(cmd[1], cmd[2]);
// 	else if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
// 		change_cd(cmd[1]);
// 	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen("wd")))
// 		get_pwd();
// 	else if (!ft_strncmp(cmd[0], "env", ft_strlen("env")))
// 		cmd_env();
// 	else if (!ft_strncmp(cmd[0], "exit", ft_strlen("exit")))
// 		cmd_exit();
// 	else if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
// 		cmd_echo(cmd[2], cmd[1]);
// 	return (1);
// }
