/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/22 02:48:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	exec_cmd_help(int *i, char **cmd, char **env)
{
	char	**path;
	int		j;

	j = *i;
	if (**cmd != '.' && **cmd != '/')
		path = ft_path(env, cmd[0], &j);
	else
	{
		path = ft_binary_path(cmd[0]);
		execve(path[0], cmd, env);
	}
	if (!path || execve(path[j], cmd, env) == -1)
		path_fault(path, cmd, env);
	ft_free_tab(cmd);
}

void	ft_exec_cmd(t_list *lst, char **cmd, int i)
{
	t_data	*temp;
	char	**env;
	int		j;

	temp = _data();
	sig_choice(0);
	temp->pid[i] = fork();
	if (temp->pid[i] == 0)
	{
		sig_choice(1);
		j = 0;
		env = ft_convert_dict_tab();
		if (temp->nb_cmd > 1)
			ft_link_fd(i);
		cmd = ft_exec_redir(&lst);
		if (g_value == 2)
			free_exec(cmd, env);
		if (is_builtin(cmd[0]))
		{
			ft_exec_builtin(cmd);
			free_exec(cmd, env);
		}
		exec_cmd_help(&j, cmd, env);
	}
}

static void	exec_help(char **cmd)
{
	ft_free_tab(cmd);
	multi_cmd_exec();
	ft_close_fd();
	ft_waitpid();
}

void	ft_exec(void)
{
	t_data	*data;
	char	**cmd;

	data = _data();
	help_exec();
	cmd = ft_clean_redirection(_lst()->token->cmd);
	if (!cmd || !cmd[0])
	{
		free(data->pid);
		free(data->fd);
		unlink_hd();
		return ;
	}
	sig_choice(2);
	if (data->nb_cmd == 1 && is_builtin(cmd[0]))
		super_exec_helper(cmd);
	else
		exec_help(cmd);
	free(data->pid);
	free(data->fd);
	unlink_hd();
}
