/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:13 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 11:39:53 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_cmd_one(char **cmd)
{
	if (ft_tablen(cmd) > 2)
	{
		g_value = 1;
		ft_free_tab(cmd);
		printf("exit\nMinishell: exit: too many arguments\n");
		free(_data()->pid);
		free(_data()->fd);
		hasta_la_vista(0);
	}
	else if (!cmd[1])
	{
		ft_free_tab(cmd);
		free(_data()->pid);
		free(_data()->fd);
		printf("exit\n");
		hasta_la_vista(0);
	}
}

static void	exit_cmd_two(char **cmd)
{
	if (ft_str_is_numeric(cmd[1]))
	{
		g_value = ft_atoi(cmd[1]);
		ft_free_tab(cmd);
		free(_data()->pid);
		free(_data()->fd);
		printf("exit\n");
		hasta_la_vista(0);
	}
	else
	{
		g_value = 255;
		free(_data()->pid);
		free(_data()->fd);
		printf("exit\n");
		printf("Minishell: %s: numeric argument required\n", cmd[1]);
		ft_free_tab(cmd);
		hasta_la_vista(0);
	}
}

void	exit_cmd(char **cmd)
{
	exit_cmd_one(cmd);
	exit_cmd_two(cmd);
}
