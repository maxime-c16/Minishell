/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:21:50 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/10 12:57:32 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pipe_fd(int **fd)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	while (i < data->nb_cmd - 1)
	{
		if (pipe(fd[i]) == -1)
			hasta_la_vista();
		i++;
	}
}

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

int	**init_fd()
{
	int		**fd;
	int		i;
	t_data	*data;

	data = _data();
	fd = malloc(sizeof(int *) * (data->nb_cmd + 1));
	if (fd == NULL)
		hasta_la_vista();
	i = 0;
	while (i < data->nb_cmd - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		fd[i][0] = 0;
		fd[i][1] = 0;
		if (fd[i] == NULL)
			hasta_la_vista();
		i++;
	}
	pipe_fd(fd);
	return (fd);
}

void	init_new_token(char **env)
{
	t_list	*data;

	data = _lst();
	ft_lstadd_back(&data, ft_lstnew(env));
	return ;
}
