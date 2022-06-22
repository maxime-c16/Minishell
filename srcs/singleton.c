/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:26:30 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/21 18:27:45 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*_lst(void)
{
	static t_list	lst;
	static int		init = 0;

	if (init == 0)
	{
		init = 1;
		ft_bzero(&lst, sizeof(t_list));
	}
	return (&lst);
}
