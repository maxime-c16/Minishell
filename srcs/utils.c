/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:30:24 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/10 15:37:17 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_int_tab(int **tab, int size)
{
	int i;

	i = 0;
	dprintf(2, "tab :\n");
	while (i < size)
	{
		dprintf(2, "tab[i][0] = %d, ", tab[i][0]);
		dprintf(2, "tab[i][1] = %d\n", tab[i][1]);
		i++;
	}
}