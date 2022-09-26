/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:32:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/14 14:30:31 by yschecro         ###   ########.fr       */
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
		ft_free_tab(lst->h_docs->file_n);
		free(lst->h_docs);
		free(lst->token);
		bzero(lst, sizeof(t_list));
		lst = tmp;
	}
}

void	free_env(t_dic *env)
{
	int	i;

	i = 0;
	while (i < _data()->env_len)
	{
		free(env[i].key);
		free(env[i].value);
		i++;
	}
	free(env);
}

void	free_data()
{
	t_data	*data;

	data = _data();
	free(data->fd);
	free(data->pid);	
}

void	hasta_la_vista(int flag)
{
	t_list	*lst;

	lst = _lst();
	// close(_data()->save_in);
	// close(_data()->save_out);
	if (lst->token)
	{
		ft_free_lst(lst);
	}
	free_data();
	if (flag == 0)
	{
		free_env(_data()->env);
		exit(g_value); //free data
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
