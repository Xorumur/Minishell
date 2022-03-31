#include "../../includes/minishell.h"

char	*get_pwd(char	**env)
{
	char	pwd[1000];
	char	*res;

	res = getcwd(pwd, sizeof(pwd));
	return (res);
}


char	*change_cd(char	*directory, char **env)
{
	char	*path;

	path = get_pwd(env);
	path = ft_strjoin(path, directory);
	if (access(path, X_OK) == -1)
		return ;
	chdir(path);
	free(path);
}