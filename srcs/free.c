/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:32:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/03 10:28:28 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (lst)
	{
		dprintf(2, "freeing :\n");
		ft_print_tab(lst->token->cmd);
		tmp = lst->next;
		ft_free_tab(lst->token->cmd);
		ft_free_tab(lst->h_docs->limit_herdocs);
		free(lst->h_docs->fd);
		ft_free_tab(lst->h_docs->file_n);
		free(lst->h_docs);
		free(lst->token);
		bzero(lst, sizeof(t_list));
		if (i)
			free(lst);
		lst = tmp;
		i++;
	}
	if (i)
		free(lst);
}

void	free_env(t_dic *env)
{
	int	i;

	i = 0;
	while (i < _data()->env_len)
	{
		if (env[i].key)
			free(env[i].key);
		if (env[i].value)
			free(env[i].value);
		i++;
	}
	free(env);
}

void	free_data(void)
{
	t_data	*data;

	data = _data();
	if (data)
	{
		free_env(_data()->env);
	}
}

void	hasta_la_vista(int flag)
{
	t_list	*lst;

	lst = _lst();
	close(_data()->save_in);
	close(_data()->save_out);
	dprintf(2, "before free lst\n");
	ft_print_lst();
	if (lst->token)
	{
		ft_free_lst(lst);
	}
	if (flag == 0)
	{
		free_data();
		exit(g_value);
	}
	dprintf(2, "after free lst\n");
	if (!lst->next)
		dprintf(2, "lst is null\n");
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (!tab)
		return ;
	free(tab);
}
