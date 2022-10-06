/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:06:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/30 16:55:08 by yschecro         ###   ########.fr       */
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
	if (!cmd[i][0])
		printf("\n");
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

void	exit_cmd(char **cmd)
{
	if (ft_tablen(cmd) > 2)
	{
		g_value = 1;
		ft_free_tab(cmd);
		printf("Minishell: exit: too many arguments\n");
	}
	else if (!cmd[1])
	{
		ft_free_tab(cmd);
		hasta_la_vista(0);
	}
	else if (ft_str_is_numeric(cmd[1]))
	{
		g_value = ft_atoi(cmd[1]);
		ft_free_tab(cmd);
		hasta_la_vista(0);
	}
	else
	{
		g_value = 255;
		printf("Minishell: %s: numeric argument required\n", cmd[1]);
		ft_free_tab(cmd);
		hasta_la_vista(0);
	}
}

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		hasta_la_vista(0);
	printf("%s\n", pwd);
	free(pwd);
}

void	cd_cmd(char **cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		hasta_la_vista(0);
	if (chdir(cmd[1]) == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n", cmd[1]);
		return ;
	}
	search_and_replace_pwd(getcwd(NULL, 0), pwd);
}
