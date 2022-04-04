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