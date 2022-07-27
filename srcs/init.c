/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:21:50 by mcauchy           #+#    #+#             */
/*   Updated: 2022/07/26 13:32:04 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pid(void)
{
	t_data	*temp;
	t_list	*temp2;

	temp = _data();
	temp2 = _lst();
	temp->nb_cmd = ft_lstsize(temp2);
	temp->pid = malloc(sizeof(int) * (temp->nb_cmd));
	if (temp->pid == NULL)
		hasta_la_vista();
}
