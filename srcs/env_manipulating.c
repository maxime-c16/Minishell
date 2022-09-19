/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:00:56 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/04 01:39:29 by yschecro         ###   ########.fr       */
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
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	dprintf(2, "len env: %d\n", data->env_len);
	while (i < data->env_len)
	{
		dprintf(2, "key in get_value() %s\n", key);
		dprintf(2, "len key = %d   len env>key = %d\n", ft_strlen(key), ft_strlen(data->env[i].key));
		if (ft_strlen(key) == ft_strlen(data->env[i].key))
		{
			dprintf(2, "variable trouvée\n");
			if (!ft_strncmp(key, data->env[i].key, ft_strlen(data->env[i].key)))
				return (data->env[i].value);
		}
		i++;
	}
	return (NULL);
}
