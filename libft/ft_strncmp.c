/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:05:08 by mlecherb          #+#    #+#             */
/*   Updated: 2021/10/26 15:33:01 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*s10;
	unsigned char	*s20;

	i = 0;
	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	while (i < n && (s10[i] != '\0' || s20[i] != '\0'))
	{
		if ((s10[i] - s20[i]) != 0)
			return (s10[i] - s20[i]);
		i++;
	}
	return (0);
}
