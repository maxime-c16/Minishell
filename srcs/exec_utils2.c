/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:45:36 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 16:46:09 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exec(char **cmd, char **env)
{
	ft_free_tab(env);
	ft_free_tab(cmd);
	free(_data()->pid);
	free(_data()->fd);
	hasta_la_vista(0);
}

void	ft_close_fd(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	while (i < data->nb_cmd - 1)
	{
		close(data->fd[i * 2]);
		close(data->fd[i * 2 + 1]);
		i++;
	}
}

void	ft_link_fd(int i)
{
	t_data	*temp;

	temp = _data();
	if (i == 0)
		dup2(temp->fd[1], FD_STDOUT);
	else if (i == temp->nb_cmd - 1)
		dup2(temp->fd[2 * i - 2], FD_STDIN);
	else
		ft_dup2(temp->fd[2 * i - 2], temp->fd[2 * i + 1]);
	ft_close_fd();
}
