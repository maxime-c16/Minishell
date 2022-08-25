/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:32:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/25 19:28:17 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free_tab(lst->token->cmd);
		ft_free_tab(lst->h_docs->limit_herdocs);
		free(lst->h_docs->fd);
		free(lst->h_docs);
		free(lst->token);
		bzero(lst, sizeof(t_list));
		lst = tmp;
	}
}

void	hasta_la_vista(void)
{
	t_list	*lst;

	lst = _lst();
	if (lst->token)
	{
		ft_free_lst(lst);
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
