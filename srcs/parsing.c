/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 10:31:12 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(char *cmd, char **env)
{
	char	**token;
	t_data	*data;

	data = _data();
	if (!cmd)
		hasta_la_vista(0);
	token = ft_split_parsing(cmd, ' ');
	if (!token)
		hasta_la_vista(0);
	ft_parse_and_insert(token, env);
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
	return ;
}
