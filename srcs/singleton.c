/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:26:30 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/20 20:47:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*_data(void)
{
	static t_list	data;
	static int		init = 0;

	if (init == 0)
	{
		init = 1;
		ft_bzero(&data, sizeof(t_list));
	}
	return (&data);
}
