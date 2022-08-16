/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:27:02 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/16 13:05:01 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_int_tab(int **tab, int size)
{
	int	i;

	i = 0;
	dprintf(2, "tab :\n");
	while (i < size)
	{
		dprintf(2, "tab[i][0] = %d, ", tab[i][0]);
		dprintf(2, "tab[i][1] = %d\n", tab[i][1]);
		i++;
	}
}

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

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	hasta_la_vista();
	return ;
}

void	ft_dup2(int in, int out)
{
	if (dup2(in, FD_STDIN) == -1)
		hasta_la_vista();
	if (dup2(out, FD_STDOUT) == -1)
		hasta_la_vista();
}
