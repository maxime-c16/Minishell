/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:21:50 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/17 13:26:59 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pid(void)
{
	t_data	*temp;
//	t_list	*temp2;

	temp = _data();
//	temp2 = _lst();
	temp->pid = malloc(sizeof(int) * (temp->nb_cmd));
	if (temp->pid == NULL)
		hasta_la_vista();
}

void	init_fd(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	data->fd = malloc(sizeof(int) * ((data->nb_cmd - 1) * 2));
	if (data->fd == NULL)
		hasta_la_vista();
	while (i < data->nb_cmd - 1)
	{
		if (pipe(data->fd + i * 2) == -1)
			hasta_la_vista();
		i++;
	}
	return ;
}

void	init_new_token(char **env)
{
	t_list	*data;

	data = _lst();
	ft_lstadd_back(&data, ft_lstnew(env));
	return ;
}
