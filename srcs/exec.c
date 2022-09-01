/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/01 11:41:22 by mcauchy          ###   ########.fr       */
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

void	ft_exec_cmd(t_list *lst, char **cmd, int i)
{
	char	*path;
	t_data	*temp;

	temp = _data();
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		if (temp->nb_cmd > 1)
			ft_link_fd(i);
		ft_exec_redir(&lst, &cmd);
		path = ft_path(ft_convert_dict_tab(), cmd[0]);
		if (!path || execve(path, cmd, ft_convert_dict_tab()) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd[0], 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_exec(void)
{
	t_data	*data;
	char	**cmd;

	data = _data();
	write_hd();
	close_hd();
	init_fd();
	init_pid();
	cmd = ft_clean_redirection(_lst()->token->cmd);
	if (data->nb_cmd ==  1 && is_builtin(cmd[0]))
	{
		ft_free_tab(cmd);
		ft_exec_one_builtin();
	}
	else
	{
		ft_free_tab(cmd);
		multi_cmd_exec();
	}
	ft_close_fd();
	ft_waitpid();
	unlink_hd();
}
