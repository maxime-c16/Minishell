/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/01 12:59:33 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(char *cmd, char **env)
{
	char	**token;
	t_data	*data;

	data = _data();
	cmd = refacto_token_space(cmd);
	token = ft_split_parsing(cmd, ' ');
	if (!test_env(env) || !split_env(env) || !cmd || !token)
		hasta_la_vista(1);
	token = expand(token);
	ft_parse_and_insert(token, env);
	ft_unquoting();
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
}
