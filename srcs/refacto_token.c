/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refacto_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:34:17 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/03 10:25:25 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_refacto_len(char *cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (cmd[i] && cmd[i + 1])
	{
		if (ft_isalnum(cmd[i]) && is_token(cmd[i + 1]))
			size++;
		else if (cmd[i] == '|' && (cmd[i + 1] == '\"' || cmd[i + 1] == '\''))
			size++;
		else if (cmd[i] == '|' && (cmd[i + 1] == '>' || cmd[i + 1] == '<'))
			size++;
		else if (is_token(cmd[i]) && ft_isalnum(cmd[i + 1]))
			size++;
		else if ((cmd[i] == '\"' || cmd[i] == '\'') && is_token(cmd[i + 1]))
			size++;
		else if (is_token(cmd[i]) && (cmd[i + 1] == '\"' || cmd[i + 1] == '\''))
			size++;
		i++;
	}
	return (size);
}

char	*refacto_token_space(char *cmd)
{
	char	*new_cmd;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd)
				+ ft_refacto_len(cmd) + 1));
	if (!new_cmd)
		hasta_la_vista(1);
	ft_bzero(new_cmd, ft_strlen(cmd) + ft_refacto_len(cmd) + 1);
	while (cmd[i] && cmd[i + 1])
	{
		refacto_help(&new_cmd, cmd, &i);
		i++;
	}
	if (cmd[i])
		new_cmd = ft_strjoin_char(new_cmd, cmd[i]);
	return (new_cmd);
}
