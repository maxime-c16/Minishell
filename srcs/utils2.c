/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:57:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/25 18:59:57 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_lst_heredocs_len(t_list *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lst->token->cmd[i])
	{
		if (!ft_strcmp(lst->token->cmd[i], "<<"))
			j++;
		i++;
	}
	return (j);
}

int	ft_lst_heredocs(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = _lst();
	while (tmp)
	{
		tmp->hd_node = ft_lst_heredocs_len(tmp);
		i += tmp->hd_node;
		tmp = tmp->next;
	}
	return (i);
}
