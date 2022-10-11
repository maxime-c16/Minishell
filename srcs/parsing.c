/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/10/11 15:56:11 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(char *cmd)
{
	char	**token;
	t_data	*data;

	data = _data();
	cmd = refacto_token_space(cmd);
//	token = ft_split(cmd, ' ');
	token = lcd_split(cmd);
	if (!cmd || !token)
		hasta_la_vista(0);
//	ft_print_tab(token);
	token = expand(token);
//	ft_print_tab(token);
//	printf("avant parse\n");
	ft_parse_and_insert(token);
//	printf("apres parse\n");
//	ft_print_lst();
//	dprintf(2, "-----------unquoting--------------\n");
	ft_unquoting();
	data->nb_cmd = ft_lst_size_without_pipe();
	limit_heredocs();
	free(cmd);
}
