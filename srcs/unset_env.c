/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:31:55 by hrecolet          #+#    #+#             */
/*   Updated: 2022/09/01 11:56:43 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	choose_unset_var(char *str)
{
	t_data	*data;
	int		i;

	data = _data();
	i = 0;
	if (!str)
		return (-1);
	while (i < data->env_len)
	{
		if (ft_strncmp(str, data->env[i].key, ft_strlen(str)) == 0)
		{
			if (!ft_strncmp(data->env[i].key, str, ft_strlen(data->env[i].key)))
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

void	cpy_dic(int *i, int *j, t_dic **new_dic)
{
	t_data	*data;

	data = _data();
	(*new_dic)[*j].key = ft_strdup(data->env[*i].key);
	if (!(*new_dic)[*j].key)
		hasta_la_vista(0);
	(*new_dic)[*j].value = ft_strdup(data->env[*i].value);
	if (!(*new_dic)[*j].value)
		hasta_la_vista(0);
	(*i)++;
	(*j)++;
}

void	unset_var(char *str)
{
	t_data	*data;
	t_dic	*new_dic;
	int		i;
	int		j;
	int		index_to_del;

	data = _data();
	i = 0;
	j = 0;
	index_to_del = choose_unset_var(str);
	if (index_to_del == -1)
		return ;
	new_dic = malloc(sizeof(t_dic) * (data->env_len - 1));
	if (!new_dic)
		hasta_la_vista(0);
	while (i < index_to_del)
		cpy_dic(&i, &j, &new_dic);
	i++;
	while (i < data->env_len)
		cpy_dic(&i, &j, &new_dic);
	data->env_len--;
}
