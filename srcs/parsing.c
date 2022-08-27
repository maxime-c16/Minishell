/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/27 18:12:01 by yschecro         ###   ########.fr       */
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

int	parsing(char *cmd, char **env)
{
	char	**token;
	t_data	*data;

	data = _data();
	if (!test_env(env))
		hasta_la_vista();
	if (!split_env(env))
		hasta_la_vista();
	if (!cmd)
		hasta_la_vista();
	token = ft_split_parsing(cmd, ' ');
	if (!token)
		hasta_la_vista();
	token = expand(token);
//	debug_token(token);
	ft_parse_and_insert(token, env);
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
  return (1);
}
