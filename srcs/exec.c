/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/10/03 18:58:33 by yschecro         ###   ########.fr       */
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
	char	**env;
	t_data	*temp;

	temp = _data();
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		env = ft_convert_dict_tab();
		if (temp->nb_cmd > 1)
			ft_link_fd(i);
		ft_exec_redir(&lst, &cmd);
		if (is_builtin(cmd[0]))
		{
			ft_exec_builtin(cmd);
			hasta_la_vista(1);
		}
		path = ft_path(env, cmd[0]);
		if (!path || execve(path, cmd, env) == -1)
		{
			free(path);
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd[0], 2);
			hasta_la_vista(1);
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
	if (data->nb_cmd == 1 && is_builtin(cmd[0]))
	{
		ft_free_tab(cmd);
		ft_exec_one_builtin();
		ft_close_fd();
	}
	else
	{
		ft_free_tab(cmd);
		multi_cmd_exec();
		ft_close_fd();
		ft_waitpid();
	}
//	if (!is_builtin(cmd[0]) && data->nb_cmd > 1)
	unlink_hd();
}
