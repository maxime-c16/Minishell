/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:28:21 by yoseph            #+#    #+#             */
/*   Updated: 2022/11/21 02:26:29 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	test_env(char **env)
{
	t_data	*data;

	data = _data();
	if (data->env)
		free(data->env);
	if (!env)
		return (0);
	return (1);
}

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	int		len;
	char	*out;

	len = ft_strlen(str);
	out = malloc(sizeof(char) * len + 1);
	if (!out)
		return (0);
	i = 0;
	while (i < n && str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

t_data	*malloc_env(char **ev)
{
	t_data	*data;

	data = _data();
	data->env = malloc(sizeof(t_dic) * len_env(ev) + 2);
	if (!data->env)
		hasta_la_vista(0);
	return (data);
}

int	split_env(char **ev)
{
	int		i;
	int		j;
	int		k;
	t_data	*data;

	i = 0;
	data = malloc_env(ev);
	data->env_len = len_env(ev);
	while (ev[i])
	{
		j = 0;
		while (ev[i][j] != '=')
			j++;
		data->env[i].key = ft_strndup(ev[i], j);
		k = j + 1;
		j = 0;
		while (ev[i][j + k])
			j++;
		data->env[i].value = ft_strndup(ev[i] + k, j);
		if (!data->env[i].value || !data->env[i].key)
			return (0);
		i++;
	}
	return (1);
}
