/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:50:35 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/22 13:25:38 by mcauchy          ###   ########.fr       */
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

void	ft_redirections(char **token, int *i, t_list **lst, char **env)
{
	t_list		*data;
	static int	k = 1;
	int			j;
	int			l;

	l = 0;
	j = *i;
	data = *lst;
	while (data->next)
		data = data->next;
	if (strncmp(token[j - 1], "|", 1) == 0 || !token[j])
	{
		data->token = malloc(sizeof(t_token));
		data->help = malloc(sizeof(t_help));
		if (!data->token || !data->help)
			hasta_la_vista();
		data->help->env = env;
		if (token[j])
			data->token->cmd = malloc(sizeof(char *) * (j - k + 1));
		else
			data->token->cmd = malloc(sizeof(char *) * (j - k + 2));
		while (k < j)
		{
			data->token->cmd[l] = ft_strdup(token[k - 1]);
			k++;
			l++;
		}
		if (!token[j])
		{
			data->token->cmd[l] = token[j - 1];
			data->token->cmd[l + 1] = NULL;
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
