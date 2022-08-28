/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:06:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 15:50:02 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_arg(char *cmd)
{
	int	i;
	int	size;

	i = 1;
	size = ft_strlen(cmd);
	if (cmd[0] == '\0')
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
	hasta_la_vista(0);
}

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		hasta_la_vista(0);
	printf("%s\n", pwd);
	free(pwd);
}
