/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:14:46 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/21 02:19:49 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*strjoin_conv_dict(char *s1, char const *s2)
{
	char	*output;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		output[j++] = s1[i++];
	i = 0;
	while (s2[i])
		output[j++] = s2[i++];
	output[j] = '\0';
	return (free(s1), output);
}

char	**ft_convert_dict_tab(void)
{
	t_data	*data;
	char	**env;
	int		i;

	i = 0;
	data = _data();
	env = ft_calloc(sizeof(char *), (data->env_len + 1));
	if (!env)
		hasta_la_vista(0);
	while (i < data->env_len)
	{
		env[i] = ft_strdup(data->env[i].key);
		env[i] = strjoin_conv_dict(env[i], "=");
		env[i] = strjoin_conv_dict(env[i], data->env[i].value);
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

char	**ft_binary_path(char *cmd)
{
	char	**path;

	path = malloc(sizeof(char *) * 2);
	if (!path)
		hasta_la_vista(1);
	path[0] = ft_strdup(cmd);
	path[1] = NULL;
	return (path);
}

char	**ft_tabcpy(char **tab)
{
	char	**new;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		hasta_la_vista(1);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
