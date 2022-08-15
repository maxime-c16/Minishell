/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:13:06 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/14 13:52:56 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redir(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">", 1) == 0)
			return (1);
		if (ft_strncmp(cmd[i], "<", 1) == 0)
			return (1);
		if (ft_strncmp(cmd[i], ">>", 2) == 0)
			return (1);
		if (ft_strncmp(cmd[i], "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	**ft_fill_cmd(char **cmd, char **new_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">", 2) && ft_strncmp(cmd[i], "<", 2))
		{
			new_cmd[i] = ft_strdup(cmd[i]);
			if (!new_cmd[i])
				hasta_la_vista();
			i++;
		}
		else
			break ;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

char	**ft_clean_redir_cmd(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">", 2) && !ft_strncmp(cmd[i], "<", 2))
			break ;
		i++;
	}
	new_cmd = malloc(sizeof(char *) * (i + 1));
	if (!new_cmd)
		hasta_la_vista();
	new_cmd = ft_fill_cmd(cmd, new_cmd);
	return (new_cmd);
}
