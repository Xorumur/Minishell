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
		if (!ft_strncmp(tmp->name, name, ft_strlen(tmp->name)))
		{
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = ft_strdup(content);
			return ;
		}
		tmp = tmp->next;
	}

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
		g_data.exec = 0;
        return(1);
    }
	tmp = tmp->next;
	while (cmd[i])
	{
		content = NULL;
		while (ft_iswspace(cmd[i]))
			i++;
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
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
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
            i++;
		if (!cmd[i])
		{
			if (new_env)
				free(new_env);
			return (1);
		}
		if (cmd[i] == ' ')
		{
			if (tmp->next)
			{
				free(new_env);
				new_env = NULL;
				continue ;
			}
			else
			{
				free(new_env);
				return (1);
			}
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
		// if (cmd[i] == ' ')
		// {
		// 	i++;
		// }
		// if (!cmd[i] || ft_iswspace(cmd[i]) == 1)
		// {
		// 	content = NULL;
		// 	while (tmp->token->e_type != 1 && tmp)
		// 		tmp = tmp->next;
		// 	tmp = tmp->next;
		// }
		// On verifie qu'après la chié de = y'a pas un token vide ou rien
		// Si y'a un token vide sur le charactère juste après les = on skip le texte
		// Passe dire le else derière et va ajouter la variable
		// Rentre que si le token est vide.
		else if (tmp && cmd[i] && ft_iswspace(cmd[i]) != 1 && tmp->token->value[0] == 0)
		{
			while (cmd[i] && ft_isprint(cmd[i]) > 0 && ft_iswspace(cmd[i]) != 1)
				i++;
			if (tmp->next)
				tmp = tmp->next;
		}
		else  //if (ft_iswspace(cmd[i]) != 1)
		{
			content = ft_strdup(tmp->token->value);
			tmp = tmp->next;
			if (cmd[i] && ft_isquote(cmd[i]) == 1)
			{
				while (cmd[i] && ft_isquote(cmd[++i]) != 1)
					i++;
				if (cmd[i + 1])
					i++;
			}
			else 
			{
				while (ft_iswspace(cmd[i]) == 0 && cmd[i])
					i++;
			}
		}
		if (env_exist(new_env) == 0)
			ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
		else
			cmd_unset_assist(new_env, content);
		free(new_env);
		new_env = NULL;
		free(content);
		content = NULL;
	}
	free(new_env);
	if (content)
		free(content);
	g_data.exec = 0;
    return (1);
}