/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/23 12:56:17 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*parsing(char *cmd, char **env)
{
	t_list	*data;
	char	**token;
	int		i;
	int		j;

	data = _lst();
	i = 1;
	j = 1;
	token = ft_split_parsing(cmd, ' ');
	data->token = malloc(sizeof(t_token));
	data->help = malloc(sizeof(t_help));
	while (token[i - 1])
	{
		ft_redirections(token, &i, &data, env);
		i++;
	}
	return (data);
}
