#include "../includes/minishell.h"

char	*ft_realloc(char *src, int size)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	free(src);
	dest[i] = '\0';
	return (dest);
}

char	**realloc_tab(char	**t, int size)
{
	int		i;
	int		j;
	char	**dest;

	dest = malloc(sizeof(char *) * size);
	if (dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (t[i])
	{
		dest[i] = ft_strcpy(dest[i], t[i]);
		i++;
		j++;
	}
	free_tab(t);
	dest[i] = NULL;
	return (dest);
}

// char	**ft_tabdup(char **t)
// {
// 	int		i;
// 	char	**dest;

// 	i = 0;
// 	dest = malloc(sizeo(char *) * tab_size(t) + 1);
// 	while (t[i])
// 	{
// 		dest[i] = ft_strdup(t[i]);
// 		i++;
// 	}

// }

int	tab_size(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

void	print_tab(char **x)
{
	int	i;

	i = 0;
	// printf("PASSAGE\n");
	while (x[i])
	{
		ft_putstr_fd(x[i], 1);
		i++;
		ft_putchar_fd('\n', 1);
	} 
}