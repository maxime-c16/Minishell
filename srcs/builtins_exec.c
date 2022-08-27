/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:06:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/27 15:54:57 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_arg(char *cmd)
{
	int	i;
	int	size;

	i = 1;
	size = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[0] == '-')
		{
			i++;
			while (cmd[i] && cmd[i] == 'n')
				i++;
		}
	}
	if (i == size)
		return (1);
	return (0);
}

void	echo_cmd(char **cmd)
{
	int	i;
	int	res;

	i = 1;
	res = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
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

void	exit_cmd(void)
{
	hasta_la_vista();
}

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		hasta_la_vista();
	printf("%s\n", pwd);
	free(pwd);
}
