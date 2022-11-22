/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:31:36 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/22 01:43:53 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void	print_env(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	while (i < data->env_len)
	{
		printf("%s", data->env[i].key);
		printf("=");
		if (data->env[i].value)
			printf("%s", data->env[i].value);
		printf("\n");
		i++;
	}
}
