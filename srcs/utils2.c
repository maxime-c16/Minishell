/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:57:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/01 10:49:51 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

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

void	unlink_hd(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = _lst();
	while (tmp)
	{
		i = 0;
		if (tmp->hd_node > 0)
		{
			while (tmp->h_docs->file_n[i])
			{
				if (unlink(tmp->h_docs->file_n[i]) == -1)
					hasta_la_vista(0);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void	search_and_replace_pwd(char *old_pwd, char *pwd)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	while (data->env[i].key)
	{
		if (!ft_strcmp(data->env[i].key, "PWD"))
		{
			free(data->env[i].key);
			data->env[i].key = ft_strdup("PWD");
			free(data->env[i].value);
			data->env[i].value = ft_strdup(pwd);
		}
		else if (!ft_strcmp(data->env[i].key, "OLDPWD"))
		{
			free(data->env[i].key);
			data->env[i].key = ft_strdup("OLDPWD");
			free(data->env[i].value);
			data->env[i].value = ft_strdup(old_pwd);
		}
		i++;
	}
}
