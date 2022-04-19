#include "../../includes/minishell.h"

int ft_alloc_size(char *cmd, int i)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1))
        i++;
    return (i + 1);
}

static void	cmd_unset_assist(char *name, char *content)
{
	t_env	*env;
	t_env	*start;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	while (env)
	{
		if (!ft_strncmp(name, env->name, ft_strlen(name)))
		{
			printf("Adresse ici : %p\n", env->content);
			free(env->content);
			env->content = NULL;
			env->content = ft_strdup(content);
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}

int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
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
    while (cmd[i])
    {
        while (ft_iswspace(cmd[i]))
			i++;
        if (cmd[i] && ft_isquote(cmd[i]) == 1)
            i++;
		new_env = malloc(sizeof(char) * ft_alloc_size(cmd, &i));
		j = 0;
		while (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1)
		{
			new_env[j] = cmd[i];
			i++;
			j++;
		}
		new_env[j] = '\0';
        if (cmd[i] && ft_isquote(cmd[i]) == 1)
            i++;
        if (!cmd[i])
        {
            if (new_env)
                free(new_env);
            g_data.exec = 0;
            return (1);
        }
        else if (cmd[i] == '=')
        {
            i++;
            tmp = tmp->next;
			while (cmd[i] && tmp && tmp->token->e_type == 1)
			{
				if (!content)
					content = ft_strdup(tmp->token->value);
				else
					content = ft_strjoin_w(content, tmp->token->value);
				tmp = tmp->next;
				i++;
			}
        }
        if (cmd[i] && ft_isquote)
    }
}