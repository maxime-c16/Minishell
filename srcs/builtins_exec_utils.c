/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:57:34 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 02:06:02 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_arg(char *cmd)
{
	int	size_arg;
	int	i;

	i = 0;
	size_arg = ft_strlen(cmd);
	if (cmd[i] == '-')
	{
		i++;
		while (cmd[i] && cmd[i] == 'n')
			i++;
	}
	if (i == size_arg)
		return (1);
	else
		return (0);
}

static void	ft_echo_n(char **cmd)
{
	int	len_cmd;
	int	i;

	i = 2;
	len_cmd = ft_tablen(cmd);
	if (!cmd[i])
		return ;
	while (is_arg(cmd[i]) == 1)
		i++;
	while (i < len_cmd - 1)
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("%s", cmd[i]);
}

void	echo_cmd(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1] || !(*(cmd[i])))
	{
		printf("\n");
		return ;
	}
	if (is_arg(cmd[1]) == 1)
		ft_echo_n(cmd);
	else
	{
		while (cmd[i])
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("\n");
	}
	g_value = 0;
}

