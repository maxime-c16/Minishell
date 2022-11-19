/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:38:18 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 18:07:55 by mcauchy          ###   ########.fr       */
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
	static int		nb_file = 0;
	char			*itoa_file;
	int				i;

	i = 0;
	itoa_file = 0;
	while (tmp->h_docs->limit_herdocs[i])
	{
		itoa_file = ft_itoa(nb_file);
		tmp->h_docs->file_n[i] = ft_strjoin(".hdoc", itoa_file);
		free(itoa_file);
		tmp->h_docs->fd[i] = open(tmp->h_docs->file_n[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp->h_docs->fd[i] == -1)
			hasta_la_vista(0);
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

void	close_hd(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = _lst();
	while (tmp)
	{
		i = 0;
		while (i < tmp->hd_node)
		{
			close(tmp->h_docs->fd[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	ft_dup_heredocs(t_list *tmp, char **cmd, int j)
{
	int	i;

	i = 0;
	if (cmd[j + 1] == NULL)
		ft_error("syntax error near unexpected token `newline'", 2);
	else if (cmd[j + 1] && (cmd[j + 1][0] == '<' || cmd[j + 1][0] == '>'
			|| cmd[j + 1][0] == '|' || cmd[j][2] == '<' || cmd[j][2] == '>'))
		ft_error("syntax error near unexpected token `newline'", 2);
	while (i < tmp->hd_node)
	{
		tmp->h_docs->fd[i] = open(tmp->h_docs->file_n[i], O_RDONLY,
				0644);
		dup2(tmp->h_docs->fd[i], FD_STDIN);
		close(tmp->h_docs->fd[i]);
		i++;
	}
}
