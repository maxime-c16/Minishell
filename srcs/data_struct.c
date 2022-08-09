/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:09:32 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/09 12:16:24 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//Liste creer lors de l'appel du singleton

//cmd = ls -la | echo

//creer une node

//data = &node;
//data->next;
//i++;
//retour au debut de boucle;

//data-->data-->data-->NULL



void	ft_parse_and_insert(char **token, char **env)
{
	int		i;
	int		j;
	int		k;
	int		save_k;
	t_list	*data;

	i = 0;
	j = 0;
	k = 0;
	data = _lst();
	while (token[i])
	{
		data = ft_lstlast(data);
		data->token = malloc(sizeof(t_token));
		data->help = malloc(sizeof(t_help));
		data->help->env = ft_dup_tab(env);
		data->next = NULL;
		if (token[i][0] == '|')
		{
			data->token->cmd = malloc(sizeof(char *) * 2);
			data->token->cmd[0] = ft_strdup(token[i]);
			data->token->cmd[1] = NULL;
			data->token->type = PIPE;
			data->next = NULL;
			i++;
			k++;
		}
		else
		{
			j = ft_count_cmd(token, i);
			i += j;
			data->token->cmd = malloc(sizeof(char *) * (j + 1));
			data->token->cmd[j] = NULL;
			save_k = k + j;
			while (j--)
				data->token->cmd[j] = ft_strdup(token[k + j]);
			k = save_k;
			data->token->type = CMD;
		}
		if (token[i])
			init_new_token(env);
	}
	ft_free_tab(token);
}
