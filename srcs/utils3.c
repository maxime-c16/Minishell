/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:14:46 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/13 11:59:15 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_convert_dict_tab(void)
{
	t_data	*data;
	char	*temp;
	char	**env;
	int		i;

	i = 0;
	data = _data();
	env = malloc(sizeof(char *) * (data->env_len + 1));
	bzero(env, sizeof(char *) * (data->env_len + 1));
	if (!env)
		return (0);
	env[data->env_len] = NULL;
	while (i < data->env_len)
	{
		temp = ft_strjoin(env[i], data->env[i].key);
		free(env[i]);
		env[i] = temp;
		temp = ft_strjoin(env[i], "=");
		free(env[i]);
		env[i] = temp;
		temp = ft_strjoin(env[i], data->env[i].value);
		free(env[i]);
		env[i] = temp;
		i++;
	}
	return (env);
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (-1);
	return (0);
}