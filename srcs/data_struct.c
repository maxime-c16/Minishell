/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:09:32 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/27 04:36:26 by yschecro         ###   ########.fr       */
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

void	insert_if(t_list **data, int *i, int *k, char *token)
{
	(*data)->token->cmd = malloc(sizeof(char *) * 2);
	if (!(*data)->token->cmd)
		hasta_la_vista(1);
	(*data)->token->cmd[0] = ft_strdup(token);
	if (!(*data)->token->cmd[0])
		hasta_la_vista(1);
	(*data)->token->cmd[1] = NULL;
	(*data)->token->type = PIPE;
	(*data)->next = NULL;
	(*i)++;
	(*k)++;
}

void	insert_else(t_list **data, int *i, int *k, char ***token)
{
	int	j;
	int	save_k;

	j = ft_count_cmd(*token, *i);
	(*i) += j;
	(*data)->token->cmd = malloc(sizeof(char *) * (j + 1));
	if (!(*data)->token->cmd)
		hasta_la_vista(1);
	(*data)->token->cmd[j] = NULL;
	save_k = (*k) + j;
	while (j--)
		(*data)->token->cmd[j] = ft_strdup(*token[(*k) + j]);
	(*k) = save_k;
	(*data)->token->type = CMD;
}

void	ft_parse_and_insert(char **token)
{
	int		i;
	int		k;
	t_list	*data;

	i = 0;
	k = 0;
	data = _lst();
	while (token[i])
	{
		data = ft_lstlast(data);
		data->token = malloc(sizeof(t_token));
		data->next = NULL;
		if (token[i][0] == '|')
			insert_if(&data, &i, &k, token[i]);
		else
			insert_else(&data, &i, &k, &token);	
		if (token[i])
			init_new_token();
		ft_free_tab(token);
	}
}


	//void	parse_if(**lst, )
	/*
	   void	ft_parse_and_insert(char **token)
	   {
	   t_list	*lst;
	   t_list	*new;
	   int		i;
	   int		j;

	   i = 0;
	   lst = _lst();
	   while (token[i])
	   {
	   j = 0;
	   new = malloc(sizeof(t_list));
	   if (!new)
	   hasta_la_vista(1);
	   if (token[i][0] != '|')
	   {
	   while (token[i] && token[i][0] != '|')
	   {
	   new->token->cmd[j] = token[i];
	   i++;
	   j++;
	   }
	   new->token->cmd[j] = 0;
	   ft_lstadd_back(&lst, new);
	   }
	   else if (token[i][0] == '|')
	   {
	   new->token->cmd[0] = token[i];
	   ft_lstadd_back(&lst, new);
	   i++;
	   }
	   }
	   i++;
	   }*/
