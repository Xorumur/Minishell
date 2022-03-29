/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:25:30 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/29 23:42:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	count_char_c(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_check(s[i], c) == 1)
			i++;
		if (s[i] && ft_check(s[i], c) == 0)
		{
			count++;
			while (s[i] && ft_check(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

static char	*ft_alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_check(s[i], c) == 0)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_check(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static int	ft_skip(char const *s, char c, int pos)
{
	int	i;

	i = pos;
	while (s[i] && ft_check(s[i], c) == 0)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		nb_c;
	char	**dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_char_c(s, c) + 1));
	if (dest == NULL)
		return (NULL);
	nb_c = 0;
	while (s[i])
	{
		while (s[i] && ft_check(s[i], c) == 1)
			i++;
		if (s[i] && ft_check(s[i], c) == 0)
		{
			dest[nb_c++] = ft_alloc_str((s + i), c);
			i = ft_skip(s, c, i);
		}
	}
	dest[nb_c] = NULL;
	return (dest);
}
