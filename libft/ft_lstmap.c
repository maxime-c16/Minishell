/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:57:27 by maximecauch       #+#    #+#             */
/*   Updated: 2022/06/20 20:58:15 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;

	tmp = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		new = ft_lstnew((*f)(lst->token));
		if (!new)
		{
			while (tmp)
			{
				new = tmp->next;
				(*del)(tmp->token);
				free(tmp);
				tmp = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&tmp, new);
		lst = lst->next;
	}
	return (tmp);
}
