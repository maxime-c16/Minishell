/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/10 12:56:12 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_dup2(int in, int out)
{
	if (dup2(in, FD_STDIN) == -1)
		hasta_la_vista();
	if (dup2(out, FD_STDOUT) == -1)
		hasta_la_vista();
}

static void	ft_link_fd(int *fd, int i)
{
	t_data	*temp;

	temp = _data();
	if (i == 0)
	{
		ft_dup2(0, fd[1]);
		close(fd[1]);
		close(fd[0]);
	}
	else if (i == temp->nb_cmd - 1)
	{
		ft_dup2(fd[0], 1);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		ft_dup2(fd[0], fd[1]);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	ft_exec_cmd(t_list *lst, int i, int *fd)
{
	char	*path;
	t_data	*temp;

	temp = _data();
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		if (temp->nb_cmd > 1)
			ft_link_fd(fd, i);
		path = ft_path(lst->help->env, lst->token->cmd[0]);
		if (!path || execve(path, lst->token->cmd, lst->help->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(lst->token->cmd[0], 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// close(fd[1]);
		// close(fd[0]);
		waitpid(temp->pid[i], NULL, 0);
	}
}

static void	ft_exec_pipe(t_list *lst, int k, int *fd)
{
	char	**token;

	token = lst->token->cmd;
	if (!token[0][0])
		return ;
	if (token[0][0] == '|')
		return ;
	ft_exec_cmd(lst, k, fd);
}

void	ft_exec(void)
{
	t_list	*data;
	t_list	*tmp;
	int		i;
	int		**fd;

	i = 0;
	data = _lst();
	tmp = data;
	fd = init_fd();
	init_pid();
	while (tmp)
	{
		ft_exec_pipe(tmp, i, fd[i]);
		if (tmp->token->type != PIPE)
			i++;
		tmp = tmp->next;
	}
}
