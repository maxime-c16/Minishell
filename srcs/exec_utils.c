/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:30:18 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/01 10:54:06 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exec_pipe(t_list *lst, int k)
{
	char	**token;

	token = lst->token->cmd;
	if (!token[0][0])
		return ;
	if (token[0][0] == '|')
		return ;
	ft_exec_cmd(lst, token, k);
}

void	multi_cmd_exec(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = _lst();
	while (tmp)
	{
		ft_exec_pipe(tmp, i);
		if (tmp->token->type != PIPE)
			i++;
		tmp = tmp->next;
	}
}

static void	ft_exec_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		exit_cmd();
	if (!ft_strcmp(cmd[0], "echo"))
		echo_cmd(cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd_cmd();
	if (!ft_strcmp(cmd[0], "env"))
		print_env();
	if (!ft_strcmp(cmd[0], "export"))
		add_to_env(cmd[1]);
	if (!ft_strcmp(cmd[0], "unset"))
		unset_var(cmd[1]);
}

static void	ft_exec_one_builtin(t_list *tmp)
{
	char	**cmd;
	int		save_in;
	int		save_out;

	save_in = dup(0);
	save_out = dup(1);
	cmd = tmp->token->cmd;
	ft_exec_redir(&tmp, &cmd);
	ft_exec_builtin(cmd);
	dup2(save_in, 0);
	dup2(save_out, 1);
}

void	one_builtin_exec(void)
{
	t_list	*tmp;

	tmp = _lst();
	ft_exec_one_builtin(tmp);
}
