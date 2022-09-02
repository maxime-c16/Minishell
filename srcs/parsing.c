/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/02 18:51:00 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(char *cmd)
{
	char	**token;
	t_data	*data;

	data = _data();
	cmd = refacto_token_space(cmd);
	token = ft_split_parsing(cmd, ' ');
	if (!cmd || !token)
		hasta_la_vista(0);
	token = expand(token);
	ft_parse_and_insert(token);
	ft_unquoting();
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
}
