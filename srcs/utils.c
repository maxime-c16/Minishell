/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/08/10 15:30:24 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/10 15:37:17 by mcauchy          ###   ########.fr       */
=======
/*   Created: 2022/08/11 10:27:02 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/11 11:56:33 by mcauchy          ###   ########.fr       */
>>>>>>> 86b3579359f7ed77c8f88a26a37715882ebf8e2e
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
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
=======
int	ft_lst_size_without_pipe(void)
{
	t_list	*lst;
	int		size;

	lst = _lst();
	size = 0;
	while (lst)
	{
		if (lst->token->type != PIPE)
			size++;
		lst = lst->next;
	}
	return (size);
}

void	ft_waitpid(void)
{
	t_data	*data;
	int		i;

	data = _data();
	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
}
>>>>>>> 86b3579359f7ed77c8f88a26a37715882ebf8e2e
