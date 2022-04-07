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
				(*token) = (*token)->next->next;
				return ;
			}
			if (!line)
				line = ft_strdup(temp);
			else
				temp = ft_strjoin(line, temp);
			line = ft_strjoin(temp, "\n");
            free(temp);
		}
    }
}

void	write_fd(char *path, int fd)
{
	char	buf[2];
	int		len;
	char	*line;
    int     fdin;

    fdin = open(path, O_RDONLY);
	len = read(fdin, buf, 1);
	buf[1] = '\0';
	line = ft_strdup(buf);
	len = read(fdin, buf, 1);
	buf[1] = '\0';
	while (len > 0)
	{
		line = ft_strjoin(line, buf);
		len = read(fdin, buf, 1);
		buf[1] = '\0';
	}
	ft_putstr_fd(line, fd);
    close(fdin);
	free(line);
}

int	builtins(char *cmd)
{
	int	retour;

	retour = 0;
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset"))) // FAIT
    	retour = 1;
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		retour = 1;
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd"))) // FAIT
        retour = 1;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd"))) // FAIT
    	retour = 1;
	else if (!ft_strncmp(cmd, "env", ft_strlen("env"))) // FAIT
		retour = 1;
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo"))) // FAIT
		retour = 1;
	return (retour);
}

int	is_builtins(char **cmd, int redir, int in)
{
    int retour;

    retour = 0;
	if (in != -1)
		dup2(in, STDIN_FILENO);
	if (redir != -1 && redir != 24640)
		dup2(redir, STDOUT_FILENO);
	if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset"))) // FAIT
    	retour = cmd_unset(cmd);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
		retour = export_cmd();
	else if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd"))) // FAIT
        retour = change_cd(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen("pwd"))) // FAIT
    	retour = get_pwd();
	else if (!ft_strncmp(cmd[0], "env", ft_strlen("env"))) // FAIT
		retour = cmd_env();
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo"))) // FAIT
		retour = cmd_echo(cmd);
	return (retour);
}
