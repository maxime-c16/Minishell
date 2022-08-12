/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/11 12:02:49 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_close_fd(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	while (i < data->nb_cmd - 1)
	{
		close(data->fd[i * 2]);
		close(data->fd[i * 2 + 1]);
		i++;
	}
}

static void	ft_dup2(int in, int out)
{
	if (dup2(in, FD_STDIN) == -1)
		hasta_la_vista();
	if (dup2(out, FD_STDOUT) == -1)
		hasta_la_vista();
}

static void	ft_link_fd(int i)
{
	t_data	*temp;

	temp = _data();
	if (i == 0)
		dup2(temp->fd[1], FD_STDOUT);
	else if (i == temp->nb_cmd - 1)
		dup2(temp->fd[2 * i - 2], FD_STDIN);
	else
		ft_dup2(temp->fd[2 * i - 2], temp->fd[2 * i + 1]);
	ft_close_fd();
}

static void	ft_exec_cmd(t_list *lst, int i)
{
	char	*path;
	t_data	*temp;

	temp = _data();
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		if (temp->nb_cmd > 1)
			ft_link_fd(i);
		path = ft_path(lst->help->env, lst->token->cmd[0]);
		if (!path || execve(path, lst->token->cmd, lst->help->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(lst->token->cmd[0], 2);
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_exec_pipe(t_list *lst, int k)
{
	char	**token;

	token = lst->token->cmd;
	if (!token[0][0])
		return ;
	if (token[0][0] == '|')
		return ;
	ft_exec_cmd(lst, k);
}

void	ft_exec(void)
{
	t_list	*data;
	t_list	*tmp;
	int		i;

	i = 0;
	data = _lst();
	tmp = data;
	init_fd();
	init_pid();
	while (tmp)
	{
		ft_exec_pipe(tmp, i);
		if (tmp->token->type != PIPE)
			i++;
		tmp = tmp->next;
	}
	ft_close_fd();
	ft_waitpid();
}
