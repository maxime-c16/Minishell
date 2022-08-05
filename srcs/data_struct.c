/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:09:32 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/05 15:37:12 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//this file is used to create the data structure used in the program
//the data structure is a list of tokens
//each token is a list of commands
//the pipe cmd is in its own element of the list

#include "../includes/minishell.h"

int	ft_count_cmd(char **token, int i)
{
	int		count;

	count = 0;
	while (token[i] && token[i][0] != '|')
	{
		count++;
		i++;
	}
	return (count);
}

void	ft_parse_and_insert(char **token, char **env)
{
	int		i;
	int		j;
	t_list	*data;

	i = 0;
	j = 0;
	data = _lst();
	while (token[i])
	{
		data->token = malloc(sizeof(t_token));
		if (token[i][0] == '|')
		{
			data->token->cmd = malloc(sizeof(char *) * 2);
			data->token->cmd[0] = ft_strdup(token[i]);
			data->token->cmd[1] = NULL;
			data->token->type = PIPE;
			data->next = NULL;
			i++;
		}
		else
		{
			j = ft_count_cmd(token, i);
			i += j;
			data->token->cmd = malloc(sizeof(char *) * (j + 1));
			data->token->cmd[j] = NULL;
			while (j--)
			{
				data->token->cmd[j] = ft_strdup(token[j]);
			}
			data->token->cmd[0] = ft_strdup(token[i]);
			data->token->type = CMD;
			data->help = malloc(sizeof(t_help));
			data->help->env = env;
			data->next = NULL;
		}
		if (token[i])
			init_new_token(env);
	}
	ft_free_tab(token);
}
