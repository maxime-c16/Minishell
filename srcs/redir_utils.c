/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:13:06 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/22 01:39:24 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_help(int *i, char **cmd)
{
	int	j;

	j = *i;
	if (cmd[j][1] == '>')
		ft_redirection_right_right(cmd, j);
	else
		ft_redirection_right(cmd, j);
	if (g_value == 2)
		return (1);
	return (0);
}

static int	is_redirect(char *cmd)
{
	if (ft_strcmp(cmd, ">") == 0 || ft_strcmp(cmd, "<") == 0 || \
			ft_strcmp(cmd, ">>") == 0 || ft_strcmp(cmd, "<<") == 0)
		return (1);
	return (0);
}

static int	len_wo_redir(char **cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]) == 1)
			ret += ft_strlen(cmd[i]);
		i++;
	}
	if (i - ret == 0)
		return (-1);
	return (i - ret);
}

char	**ft_clean_redirection(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	if (len_wo_redir(cmd) == -1)
		return (NULL);
	new_cmd = ft_calloc(sizeof(char *), (len_wo_redir(cmd) + ft_strlen(*cmd) + 1));
	if (!new_cmd)
		hasta_la_vista(0);
	while (cmd[i])
	{
		if (is_redirect(cmd[i]) == 1)
		{
			i += 2;
			if ((cmd[i - 1] && !cmd[i]) || (cmd[i - 2] && !cmd[i - 1]))
				break ;
			continue ;
		}
		new_cmd[j] = ft_strdup(cmd[i]);
		if (!new_cmd[j])
			hasta_la_vista(0);
		i++;
		j++;
	}
	return (new_cmd);
}
