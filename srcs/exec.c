/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/07/21 14:07:48 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exec_cmd(t_list *lst, int j, int fd[2])
{
	int		i;
	char	*path;
	//il faut aussi malloc un tableau de pipe du nombre de fork, qui va contenir le pid de chaque fork
	//ensuite il faut faire un waitpid pour chaque fork
	i = fork();
	if (i == 0)
	{
		if (j == 0 && lst->next)
		{
			dup2(fd[1], FD_STDIN);
			close(fd[1]);
		}
		else if (!lst->next && j > 0)
		{
			dup2(fd[0], FD_STDOUT);
			close(fd[0]);
		}
		else
		{
			dup2(fd[0], FD_STDIN);
			dup2(fd[1], FD_STDOUT);
		}
		path = ft_path(lst->help->env, lst->token->cmd[0]);
		if (!path || execve(path, lst->token->cmd, lst->help->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(lst->token->cmd[0], 2);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

static void	ft_exec_pipe(t_list *lst, int k, int fd[2])
{
	char	**token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = lst->token->cmd;
	while (token[i])
	{
		if (token[i][0] == '|')
			i++;
		if (pipe(fd) == -1)
		{
			printf("pipe error\n");
			return ;
		}
		ft_exec_cmd(lst, k, fd);
		i++;
	}
}

void	ft_exec(void)
{
	t_list	*data;
	t_list	*tmp;
	int		i;
	int		fd[2];

	data = _lst();
	tmp = data;
	i = 0;
	while (tmp)
	{
		if (ft_lstsize(tmp) > 1)
			ft_exec_pipe(tmp, i, fd);
		else
			ft_exec_cmd(tmp, i, fd);
		i++;
		tmp = tmp->next;
	}
}
