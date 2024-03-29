/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:00:56 by yschecro          #+#    #+#             */
/*   Updated: 2022/10/06 14:05:09 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*lcd_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (NULL);
	while (s1[i] == s2[i])
		i++;
	if (i == ft_strlen(s1) && i == ft_strlen(s2))
		return (s1);
	else
		return (NULL);
}

char	*get_value(char *key)
{
	t_data	*data;
	int		i;
	int		len;

	data = _data();
	i = 0;
	while (i < data->env_len)
	{
		if (ft_strlen(key) < ft_strlen(data->env[i].key))
			len = ft_strlen(data->env[i].key);
		else
			len = ft_strlen(key);
		if (!ft_strncmp(key, data->env[i].key, len))
		{
			return (data->env[i].value);
		}
		i++;
	}
	return (NULL);
}
