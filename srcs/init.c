/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:21:50 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 18:25:06 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pid(void)
{
	t_data	*temp;

	temp = _data();
	temp->pid = malloc(sizeof(int) * (temp->nb_cmd));
	if (temp->pid == NULL)
		hasta_la_vista(0);
}

void	init_fd(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	data->fd = malloc(sizeof(int) * ((data->nb_cmd - 1) * 2));
	if (data->fd == NULL)
		hasta_la_vista(0);
	while (i < data->nb_cmd - 1)
	{
		if (pipe(data->fd + i * 2) == -1)
			hasta_la_vista(0);
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

void	init_heredocs(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	tmp->h_docs = malloc(sizeof(t_heredocs));
	_data()->nb_hd = ft_lst_heredocs();
	tmp->h_docs->limit_herdocs = malloc(sizeof(char *) * (tmp->hd_node + 1));
	tmp->h_docs->fd = malloc(sizeof(int) * (tmp->hd_node));
	tmp->h_docs->file_n = malloc(sizeof(char *) * (tmp->hd_node + 1));
	if (!tmp->h_docs->limit_herdocs || !tmp->h_docs->fd
		|| !tmp->h_docs->file_n)
		hasta_la_vista(0);
	tmp->h_docs->limit_herdocs[tmp->hd_node] = NULL;
	tmp->h_docs->file_n[tmp->hd_node] = NULL;
}
