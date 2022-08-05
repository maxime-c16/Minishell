/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:50:35 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/05 15:33:18 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_new_token(char **env)
{
	t_list	*data;

	data = _lst();
	ft_lstadd_back(&data, ft_lstnew(env));
	return ;
}

int	check_if_pipe(char **token, int *j, int *k, t_list **data, char **env)
{
	if (strncmp(token[(*j) - 1], "|", 1) == 0)
	{
		(*data)->token = malloc(sizeof(t_token));
		(*data)->help = malloc(sizeof(t_help));
		(*data)->token->cmd = malloc(sizeof(char *) * 2);
		if (!(*data)->token || !(*data)->help || !(*data)->token->cmd)
			hasta_la_vista();
		(*data)->token->type = PIPE;
		(*data)->token->cmd[0] = ft_strdup("|");
		(*data)->token->cmd[1] = NULL;
		init_new_token(env);
		(*data) = (*data)->next;
		(*k) = (*j);
		return (1);
	}
	return (0);
}

void	ft_insertion(char **token, int *i, t_list **lst, char **env)
{
	t_list		*data;
	static int	k = 1;
	int			j;
	int			l;

	l = 0;
	j = *i;
	data = *lst;
	if (j < k)
		k = 1;
	while (data->next)
		data = data->next;
	if (!token[j] || strncmp(token[j], "|", 1) == 0)
	{
		data->token = malloc(sizeof(t_token));
		data->help = malloc(sizeof(t_help));
		if (!data->token || !data->help)
			hasta_la_vista();
		data->help->env = env;
		if (token[j])
			data->token->cmd = malloc(sizeof(char *) * (j - k + 2));
		else
			data->token->cmd = malloc(sizeof(char *) * (j - k + 3));
		while (j > k)
		{
			data->token->cmd[l] = ft_strdup(token[k - 1]);
			k++;
			l++;
		}
		if (!token[j] || strncmp(token[j], "|", 1) == 0)
		{
			data->token->cmd[l] = ft_strdup(token[j - 1]);
			data->token->cmd[l + 1] = NULL;
			data->next = NULL;
			check_if_pipe(token, &j, &k, &data, env);
			return ;
		}
		data->token->cmd[l] = NULL;
		k = j;
		init_new_token(env);
	}
	if (!data)
		hasta_la_vista();
	return ;
}
