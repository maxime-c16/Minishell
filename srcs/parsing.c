/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/20 20:00:44 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*lcd_strjoin3000(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = ft_calloc(1, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s1 || !s2)
		return (0);
	if (!out)
		hasta_la_vista(0);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	return (free(s1), out);
}

static char	*lcd_strjoin_parse(char **str)
{
	int		i;
	char	*out;

	i = 0;
	out = ft_strdup("");
	if (!out)
		hasta_la_vista(0);
	while (str[i])
	{
		out = lcd_strjoin3000(out, str[i]);
		free(str[i]);
		out = lcd_strjoin3000(out, " ");
		i++;
	}
	free(str);
	return (out);
}

void	parsing(char *cmd)
{
	char	**token;
	t_data	*data;

	data = _data();
	cmd = refacto_token_space(cmd);
	token = lcd_split(cmd);
	if (!cmd || !token)
		hasta_la_vista(0);
	token = expand(token);
	token = lcd_split(lcd_strjoin_parse(token));
	ft_parse_and_insert(token);
	ft_unquoting();
	if (_data()->error)
		return ;
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
}
