/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:21:50 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/03 18:02:15 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_lstsize_without_pipe(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->token->type != PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_pid(void)
{
	t_data	*temp;
	t_list	*temp2;

	temp = _data();
	temp2 = _lst();
	temp->nb_cmd = ft_lstsize_without_pipe(temp2);
	temp->pid = malloc(sizeof(int) * (temp->nb_cmd));
	if (temp->pid == NULL)
		hasta_la_vista();
}
