/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:17:42 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 14:09:45 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	while (i < data->env_len)
	{
		printf("%s", data->env[i].key);
		printf("=");
		if (data->env[i].value)
			printf("%s", data->env[i].value);
		printf("\n");
		i++;
	}
}

static void	ft_free_dic(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	while (i < data->env_len)
	{
		free(data->env[i].key);
		free(data->env[i].value);
		i++;
	}
	free(data->env);
}

t_dic	*dup_env(void)
{
	t_dic	*new_dic;
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	new_dic = malloc(sizeof(t_dic) * (data->env_len + 1));
	if (!new_dic)
		hasta_la_vista(1);
	while (i < data->env_len)
	{
		new_dic[i].key = ft_strdup(data->env[i].key);
		if (!new_dic[i].key)
			hasta_la_vista(0);
		new_dic[i].value = ft_strdup(data->env[i].value);
		if (!new_dic[i].value)
			hasta_la_vista(0);
		i++;
	}
	ft_free_dic();
	return (new_dic);
}

static int	no_equal(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			ret++;
		i++;
	}
	if (ret == 1)
		return (1);
	return (0);
}

void	add_to_env(char *str)
{
	t_data	*data;
	char	**to_add;

	if (!str)
		return ;
	data = _data();
	data->env = dup_env();
	if (no_equal(str) == 0)
		return ;
	to_add = ft_split(str, '=');
	if (str[0] >= '0' && str[0] <= '9')
	{
		printf("export: not an identifier: %s\n", to_add[0]);
		ft_free_tab(to_add);
		return ;
	}
	data->env_len++;
	data->env[data->env_len - 1].key = ft_strdup(to_add[0]);
	data->env[data->env_len - 1].value = ft_strdup(to_add[1]);
	ft_free_tab(to_add);
}
