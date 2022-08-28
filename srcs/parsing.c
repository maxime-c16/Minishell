/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 17:57:06 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void debug_token(char **token)
{
	int i = 0;
	while (token[i])
	{
		printf("debug: _%s_\n", token[i]);
		i++;
	}
}

void	parsing(char *cmd, char **env)
{
	char	**token;
	t_data	*data;

	data = _data();
	token = ft_split_parsing(cmd, ' ');
	if (!test_env(env) || !split_env(env) || !cmd || !token)
		hasta_la_vista();
	token = expand(token);
	ft_parse_and_insert(token, env);
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
}
