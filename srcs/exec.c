/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/10/14 16:40:41 by yschecro         ###   ########.fr       */
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

static void	path_fault(char **path, char **cmd, char **env)
{
	if (path)
		ft_free_tab(path);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	g_value = 127;
	ft_free_tab(env);
	ft_free_tab(cmd);
	free(_data()->pid);
	free(_data()->fd);
	hasta_la_vista(0);
}

void	ft_exec_cmd(t_list *lst, char **cmd, int i)
{
	t_data	*temp;
	char	**path;
	char	**env;
	int		j;

	temp = _data();
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		j = 0;
		env = ft_convert_dict_tab();
		if (temp->nb_cmd > 1)
			ft_link_fd(i);
		cmd = ft_exec_redir(&lst);
		if (is_builtin(cmd[0]))
		{
			ft_exec_builtin(cmd);
			hasta_la_vista(0);
		}
		if (**cmd != '.' && **cmd != '/')
			path = ft_path(env, cmd[0], &j);
		else
		{
			path = ft_binary_path(cmd[0]);
			execve(path[0], cmd, env);
		}
		if (!path || execve(path[j], cmd, env) == -1)
			path_fault(path, cmd, env);
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
	free(data->pid);
	free(data->fd);
	unlink_hd();
}
