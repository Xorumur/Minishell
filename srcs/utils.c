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

void	print_tab(char **x)
{
	int	i;

	i = 0;
	while (x[i])
	{
		ft_putstr_fd(x[i], 1);
		i++;
		ft_putchar_fd('\n', 1);
	} 
}