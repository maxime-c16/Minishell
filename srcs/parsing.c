/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/20 23:20:02 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_list *data)
{
	data->token = NULL;
	data->next = NULL;
}

t_list	*parsing(char *cmd)
{
	t_list	*data;
	char	**token;
	int		i;
	int		j;
	int		k;

	data = _data();
	i = 1;
	j = 1;
	k = 0;
	token = ft_split(cmd, ' ');
	data->token = malloc(sizeof(t_token));
	while (token[i - 1])
	{
		k = 0;
		if (ft_strncmp(token[i - 1], "|", 1) == 0)
		{
			data = ft_redirections(data);
			return (data);
		}
		if (data == NULL)
			hasta_la_vista();
		i++;
	}
	return (data);
}
