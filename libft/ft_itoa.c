/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:09:42 by mlecherb          #+#    #+#             */
/*   Updated: 2022/03/29 23:31:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_noneg(long int nb)
{
	if (nb < 0)
	{
		return (-nb);
	}
	return (nb);
}

static int	ft_intlen(long int nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * (-1);
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	char		*str;
	long int	nb;

	nb = n;
	sign = 0;
	if (nb < 0)
		sign = -1;
	str = malloc(sizeof(char) * (ft_intlen(nb) + 1));
	if (str == NULL)
		return (NULL);
	str[ft_intlen(nb)] = '\0';
	len = ft_intlen(nb) - 1;
	while (len >= 0)
	{
		str[len] = '0' + ft_noneg(nb % 10);
		nb = ft_noneg(nb / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
