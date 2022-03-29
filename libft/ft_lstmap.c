/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:16:27 by mlecherb          #+#    #+#             */
/*   Updated: 2021/10/26 15:17:00 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*nelem;

	if (!lst || !f)
		return (NULL);
	nlist = NULL;
	while (lst)
	{
		nelem = ft_lstnew(f(lst->content));
		if (nelem == NULL)
		{
			ft_lstclear(&nlist, del);
			return (NULL);
		}
		ft_lstadd_back(&nlist, nelem);
		lst = lst->next;
	}
	return (nlist);
}
