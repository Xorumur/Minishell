#include "../../includes/minishell.h"

int	env_exist(char *name)
{
	t_env *tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(tmp->name)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int ft_alloc_size(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || ft_isdigit(cmd[i]) == 1))
        i++;
    return (i + 1);
}

// static void	cmd_unset_assist(char *name, char *content)
// {
// 	t_env	*env;
// 	t_env	*start;

// 	start = g_data.env;
// 	env = g_data.env;
// 	if (!name)
// 		return ;
// 	while (env)
// 	{
// 		if (!ft_strncmp(name, env->name, ft_strlen(name)))
// 		{
// 			printf("Adresse ici : %p\n", env->content);
// 			free(env->content);
// 			env->content = NULL;
// 			env->content = ft_strdup(content);
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	g_data.env = start;
// }

// int	ft_isquote(int c)
// {
// 	if (c == '"' || c == 39)
// 		return (1);
// 	return (0);
// }

// int	ft_isequal(int c)
// {
// 	if (c == '=')
// 		return (1);
// 	return (0);
// }

int export_cmd(void)
{
    t_tokenlist *tmp;
    char        *cmd;
    int         i;
    char        *new_env;
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
        while (ft_iswspace(cmd[i]))
			i++;
        if (cmd[i] && ft_isquote(cmd[i]) == 1)
            i += 2;
		new_env = ft_strdup(tmp->token->value);
		i += ft_strlen(new_env);
		if (tmp->next)
			tmp = tmp->next;
		// printf("Line : %s\n", (cmd + i));
		// printf("Char : %c\n", cmd[i]);
		// printf("new_env : %s\n", new_env);
		// printf("New token : %s\n", tmp->token->value);
		// On est bien au char suivant le variable d'environnement
		if (!cmd[i])
		{
			free(new_env);
			return (1);
		}
		else if (cmd[i] && tmp && ft_iswspace(cmd[i]) == 1)
		{
			// Faire en sorte de skip tous le reste
		}
		else if (cmd[i] && tmp && tmp->token->e_type == 1)
		{
			if (!content)
				content = ft_strdup(tmp->token->value);
			else 
				content = ft_strjoin_w(content, tmp->token->value);
			i++;
			tmp = tmp->next;
		}
		// On a passe les '='
		// Maintenant faut prendre la suite
		if (cmd[i] && ft_isquote(cmd[i]) == 1)
            i += 2;
		else if (cmd[i] && ft_iswspace(cmd[i]) != 1)
		{
			if (!content)
				content = ft_strdup(tmp->token->value);
			else 
				content = ft_strjoin_w(content, tmp->token->value);
			i += ft_strlen(new_env);
		}
		if (env_exist(new_env) == 0)
			ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
		else
			cmd_unset_assist(new_env, content);
		if (new_env)
			free(new_env);
		if (content)
			free(content);
    }
	// if (content)
	// 	free(content);
	// g_data.exec = 0;
    return (1);
}