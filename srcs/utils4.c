/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:03:15 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 15:42:07 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' \
			|| c == '\f')
		return (1);
	return (0);
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return ;
	while (tab[i])
	{
		dprintf(2, "%dth %s\n", i, tab[i]);
		i++;
	}
}

void	ft_print_lst(void)
{
	t_list	*lst;
	int		i;

	lst = _lst();
	i = 0;
	while (lst)
	{
		dprintf(2, "------------| maillon %d |----------\n", i);
		ft_print_tab(lst->token->cmd);
		lst = lst->next;
		i++;
	}
}
