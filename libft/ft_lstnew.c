/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:47:34 by maximecauch       #+#    #+#             */
/*   Updated: 2022/06/22 12:49:22 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

t_list	*ft_lstnew(char **env)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = malloc(sizeof(t_token));
	new->help = malloc(sizeof(t_help));
	if (!new->token || !new->help)
		hasta_la_vista();
	new->help->env = env;
	new->next = NULL;
	return (new);
}
