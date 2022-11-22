/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:30:18 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/22 04:08:39 by mcauchy          ###   ########.fr       */
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

void	ft_exec_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		exit_cmd(cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		echo_cmd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd_cmd();
	else if (!ft_strcmp(cmd[0], "cd"))
		cd_cmd(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		print_env();
	else if (!ft_strcmp(cmd[0], "export"))
		add_to_env(cmd[1]);
	else if (!ft_strcmp(cmd[0], "unset"))
		unset_var(cmd[1]);
}

void	ft_exec_one_builtin(void)
{
	char	**cmd;
	t_list	*tmp;

	tmp = _lst();
	ft_redirections(tmp);
	cmd = ft_clean_redirection(tmp->token->cmd);
	ft_exec_builtin(cmd);
	if (g_value != 1)
		ft_free_tab(cmd);
	dup2(_data()->save_in, 0);
	dup2(_data()->save_out, 1);
}
