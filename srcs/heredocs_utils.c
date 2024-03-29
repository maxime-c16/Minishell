/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:17:34 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/19 16:52:09 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	hd_message(char *msg)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd("1 delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("')", 2);
	ft_putstr_fd("\n", 2);
}

static void	write_forked_hd(t_list *lst, int i)
{
	char	*ret;

	while (42)
	{
		ret = readline("> ");
		if (!ret && g_value == 160903 && printf("\n"))
			hasta_la_vista(0);
		if (!ret)
			hd_message(lst->h_docs->limit_herdocs[i]);
		if (!ft_strcmp(ret, lst->h_docs->limit_herdocs[i]))
			break ;
		ft_putendl_fd(ret, lst->h_docs->fd[i]);
		free(ret);
	}
	free(ret);
	i++;
}

static void	hd_help(int *j)
{
	t_list	*lst;
	int		i;

	i = *j;
	lst = _lst();
	sig_choice(3);
	while (lst)
	{
		i = 0;
		while (i < lst->hd_node)
		{
			write_forked_hd(lst, i);
			i++;
		}
		lst = lst->next;
	}
	sig_choice(0);
}

void	write_hd(void)
{
	t_data	*data;
	int		i;
	int		pid;

	i = 0;
	data = _data();
	if (data->nb_hd == 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		hd_help(&i);
		close_hd();
		hasta_la_vista(0);
	}
	else
		waitpid(pid, NULL, 0);
}
