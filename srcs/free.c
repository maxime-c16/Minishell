/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:32:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/23 12:25:17 by mcauchy          ###   ########.fr       */
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
		free(lst->token);
		bzero(lst, sizeof(t_list));
		lst = tmp;
	}
}

void	hasta_la_vista(void)
{
	t_list	*data;

	data = _lst();
	if (data->token)
	{
		ft_free_lst(data);
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("freeing %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}
