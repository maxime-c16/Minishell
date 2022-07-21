/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:30:22 by mcauchy           #+#    #+#             */
/*   Updated: 2022/07/21 14:39:44 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//this file is used to manage the history of the shell using readline/history.h
//the history is stored in a linked list of t_history structs

t_history	*ft_create_history(char *cmd)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->next = NULL;
	return (new);
}

void   ft_add_history(t_history *history, char *cmd)
{
	t_history *tmp;

	tmp = history;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_history(cmd);
}
