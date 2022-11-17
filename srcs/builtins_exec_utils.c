/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:57:34 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/17 23:53:41 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_arg(char *cmd)
{
	int	i;
	int	size;

	i = 1;
	size = ft_strlen(cmd);
	if (!cmd[0])
		return (0);
	while (cmd[i])
	{
		if (cmd[0] == '-')
		{
			i++;
			while (cmd[i] && cmd[i] == 'n')
				i++;
		}
		i++;
	}
	if (i == size && i != 0 && i != 1)
		return (1);
	return (0);
}

void	echo_cmd(char **cmd)
{
	int	i;
	int	res;

	i = 1;
	res = 1;
	if (!cmd[i][0])
	{
		printf("\n");
		printf("akecoucou");
	}
	while (cmd[i])
	{
		if (is_arg(cmd[i]))
			printf("%s", cmd[i]);
		if (cmd[i + 1] && is_arg(cmd[i + 1]))
			printf(" ");
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		res *= is_arg(cmd[i]);
		i++;
	}
	if (res == 1)
		printf("\n");
}
