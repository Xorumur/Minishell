#include "../../includes/minishell.h"

int ft_alloc_size(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && ft_isalpha(cmd[i]) == 1)
        i++;
    return (i + 1);
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
    j = 0;
    i = 0;
    cmd = g_data.cmd;
    tmp = g_data.tokens;
    while ( i < ft_strlen("export"))
        i++;
    if (!cmd[i])
    {
        print_env(g_data.env, STDOUT_FILENO);
        return(1);
    }
    i++;
    new_env = malloc(sizeof(char) * ft_alloc_size(cmd + i));
    // printf("new cmd %s\n", g_data.cmd + i);
    while (ft_isalpha(cmd[i]) == 1)
    {
        new_env[j] = cmd[i];
        i++;
        j++;
    }
    new_env[j] = '\0';
    if (!cmd[i])
        return (1);
    if (cmd[i] == ' ')
        return (1);
    else if (cmd[i] == '=')
        i++;
    while (tmp->token->e_type != 1)
        tmp = tmp->next;
    if (tmp->next)
        content = ft_strdup(tmp->next->token->value);
    printf("new_env : %s | content %s\n", new_env, content);
    ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
    free(new_env);
    if (content)
        free(content);
    return (1);
}