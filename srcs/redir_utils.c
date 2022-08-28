/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:13:06 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/27 15:29:20 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redirect(char *cmd)
{
	if (ft_strncmp(cmd, ">", 1) == 0 || ft_strncmp(cmd, "<", 1) == 0 || \
			ft_strncmp(cmd, ">>", 2) == 0 || ft_strncmp(cmd, "<<", 2) == 0)
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
			ret += 2;
		i++;
	}
	return (i - ret);
}

char	**ft_clean_redirection(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	new_cmd = malloc(sizeof(char *) * (len_wo_redir(cmd) + 1));
	while (cmd[i])
	{
		if (is_redirect(cmd[i]) == 1)
		{
			i += 2;
			if (cmd[i] == NULL)
				break ;
			continue ;
		}
		new_cmd[j] = ft_strdup(cmd[i]);
		if (!new_cmd[j])
			hasta_la_vista();
		i++;
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}
