#include "../../includes/minishell.h"

int ft_alloc_size(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1))
        i++;
    return (i + 1);
}

void	ft_swap_env_content(char *name, char *content)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			// free(content);
			tmp->content = ft_strdup(content);
			return ;
		}
		tmp = tmp->next;
	}

}

int	i_increment(int token)
{
	if (token == 0)
		return (0);
	else if (token == 2)
		return (2);
	else if (token == 9)
		return (2);
	return (0);
}

int export_cmd(void)
{
    t_tokenlist *tmp;
    char        *cmd;
    int         i;
    char        *new_env;
    int         j;
    char        *content;

    content = NULL;
    i = 0;
    cmd = g_data.cmd;
    tmp = g_data.tokens;
    while (i < ft_strlen("export"))
        i++;
    if (!tmp->next)
    {
        print_env(g_data.env, STDOUT_FILENO);
        return(1);
    }
	while (cmd[i])
	{
		content = NULL;
		while (ft_iswspace(cmd[i]))
			i++;
		new_env = malloc(sizeof(char) * ft_alloc_size(cmd + i));
		j = 0;
		while (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1)
		{
			new_env[j] = cmd[i];
			i++;
			j++;
		}
		new_env[j] = '\0';
		if (!cmd[i])
			return (1);
		if (cmd[i] == ' ')
		{
			if (tmp->next)
				continue ;
			else 
				return (1);
		}
		else if (cmd[i] == '=')
			i++;
		if (!cmd[i] || ft_iswspace(cmd[i]) == 1)
		{
			content = NULL;
			while (tmp->token->e_type != 1 && tmp)
				tmp = tmp->next;
			tmp = tmp->next;
		}
		else
		{
			while (tmp->token->e_type != 1 && tmp)
				tmp = tmp->next;
			tmp = tmp->next;
			content = ft_strdup(tmp->token->value);
			while (ft_iswspace(cmd[i]) == 0 && cmd[i])
				i++;
		}
		if (ft_getenv(new_env) == NULL && env_exist(new_env) == 0)
			ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
		else
			ft_swap_env_content(new_env, content);
		new_env = NULL;
	}
	free(new_env);
	if (content)
		free(content);
    return (1);
}