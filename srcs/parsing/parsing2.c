#include "../../includes/minishell.h"

int heredoc(t_tokenlist **token)
{
    int     in;
    char    **doc;
    int     i;

    i = 0;
    in = open((*token)->next->token->value,
			O_WRONLY | O_CREAT | O_TRUNC, 0664);
    doc[i++] = readline("heredoc> ");
    while (!ft_strncmp(doc, (*token)->token->value),
            ft_strlen((*token)->token->value)) + 1);
    {
       doc[i++] = readline("heredoc> ");
    }
    doc[i] = NULL;
    // Split et ecrire dans le fichier chaque line avec un \n a la fin
    // return in, le fichier avec tout ce qui a ete ecrit dessus
    i = 0;
    while (doc[i])
        ft_putstr_fd(doc[i++], in);
    (*token) = (*token)->next->next;
    return (in);
}