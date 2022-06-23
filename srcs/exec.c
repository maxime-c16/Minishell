/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:33:04 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/22 13:41:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exec_cmd(t_list *lst)
{
	int		i;
	char	*path;

	i = fork();
	if (i == 0)
	{
		path = ft_path(lst->help->env, lst->token->cmd[0]);
		if (execve(path, lst->token->cmd, lst->help->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(path, 2);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

void	ft_exec(void)
{
	t_list	*data;
	t_list	*tmp;

	data = _lst();
	tmp = data;
	while (tmp)
	{
		if (tmp->token->cmd[0])
		{
			// printf("Executing command: %s\n", tmp->token->cmd[0]);
			if (ft_strncmp(tmp->token->cmd[0], "|", 1) != 0)
				ft_exec_cmd(tmp);
			// else
				//ft_exec_pipe(tmp->token->cmd);

		}
		tmp = tmp->next;
	}
}
