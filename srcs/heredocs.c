/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:38:18 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/25 19:49:29 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_heredocs(t_list *list, int *k)
{
	int		i;
	int		j;

	i = 0;
	j = *k;
	while (list->token->cmd[i])
	{
		if (!ft_strcmp(list->token->cmd[i], "<<"))
		{
			list->h_docs->limit_herdocs[j] = ft_strdup(list->token->cmd[i + 1]);
			j++;
		}
		i++;
	}
}

static void	open_heredocs(t_list *tmp)
{
	int		nb_file;
	int		i;
	char	*h_doc_file;

	i = 0;
	nb_file = 0;
	while (tmp->h_docs->limit_herdocs[i])
	{
		h_doc_file = ft_strjoin(".hdoc", ft_itoa(nb_file));
		tmp->h_docs->fd[i] = open(h_doc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp->h_docs->fd[i] == -1)
			hasta_la_vista();
		nb_file++;
		i++;
	}
}

void	limit_heredocs(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = _lst();
	while (tmp)
	{
		init_heredocs(&tmp);
		check_heredocs(tmp, &i);
		open_heredocs(tmp);
		tmp = tmp->next;
	}
}

void	ft_dup_heredocs(t_list *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->hd_node)
	{
		close(tmp->h_docs->fd[i]);
		tmp->h_docs->fd[i] = open(".hdoc0", O_RDONLY);
		dup2(tmp->h_docs->fd[i], FD_STDIN);
		close(tmp->h_docs->fd[i]);
		i++;
	}
}
