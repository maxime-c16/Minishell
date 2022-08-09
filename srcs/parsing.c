/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/09 12:12:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int test_env(char **env)
{
	if (!env)
		return 0;
	return (1);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	int		len;
	char	*out;

	dprintf(2, "duping\n");
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

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	split_env(char **ev)
{
	int		i;
	int		j;
	t_data	*data;

	j = 0;
	i = 0;
	data = _data();
	dprintf(2, "in parser\n");
	dprintf(2, "env : %s", ev[0]);
	data->env = malloc(sizeof(t_dic) * len_env(ev) + 1);
	if (data->env)
		return (0);
	while (ev[i])
	{
		while (ev[i][j] && ev[i][j] != '=')
			j++;
		dprintf(2, "skipped\n");
		data->env[i].key = ft_strndup(ev[i], j - 1);
		dprintf(2, "%d key created\n", i + 1);
		ev[i] += j + 1;
		j = 0;
		while (ev[i][j] && ev[i][j] != '\n')
			j++;
		data->env[i].value = ft_strndup(ev[i], j);
		dprintf(2, "%d value created\n", i + 1);
		ev[i] += j;
		if (!data->env[i].value || !data->env[i].key)
			return (0);
		i++;
	}
	return (1);
}

int	parsing(char *cmd, char **env)
{
	char	**token;
//	int		i;
//	int		j;

//	i = 1;
//	j = 1;
	if (!test_env(env))
		return (0);
	if (!split_env(env))
		return (0);
	if (!cmd)
		hasta_la_vista();
	token = ft_split_parsing(cmd, ' ');
	ft_parse_and_insert(token, env);
	return (1);
}
