/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refacto_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:20:55 by mcauchy           #+#    #+#             */
/*   Updated: 2022/09/28 19:06:30 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_quote(char *cmd, int index)
{
	int	i;
	int	odd;

	i = 0;
	odd = 0;
	while (cmd[i] && i < index)
	{
		if (cmd[i] == '\"')
		{
			i++;
			odd++;
			while (cmd[i] && cmd[i] != '\"' && i < index)
				i++;
			if (cmd[i] == '\"')
				odd--;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			odd++;
			while (cmd[i] && cmd[i] != '\'' && i < index)
				i++;
			if (cmd[i] == '\'')
				odd--;
		}
	}
	return (odd);
}

int	nb_quote_before_token(char *cmd, int index, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd[i] && i < index)
	{
		if (cmd[i] == c)
			nb++;
		i++;
	}
	return (nb % 2);
}

int	is_token(char cmd)
{
	if (cmd == '>' || cmd == '<' || cmd == '|')
		return (1);
	return (0);
}

int	ft_first_quote(char *cmd, int index, char c)
{
	while (cmd[index])
	{
		if (cmd[index] == c)
			return (1);
		index++;
	}
	return (0);
}

void	refacto_help(char **ad_cmd, char *cmd, int *j)
{
	int		i;
	char	*new_cmd;

	i = *j;
	new_cmd = *ad_cmd;
	new_cmd = ft_strjoin_char(new_cmd, cmd[i]);
	if (ft_isalnum(cmd[i]) && is_token(cmd[i + 1]))
		new_cmd = ft_strjoin(new_cmd, " ");
	else if (cmd[i] == '|' && (cmd[i + 1] == '\"' || cmd[i + 1] == '\'')
		&& !is_in_quote(cmd, i))
		new_cmd = ft_strjoin(new_cmd, " ");
	else if (cmd[i] == '|' && (cmd[i + 1] == '>' || cmd[i + 1] == '<'))
		new_cmd = ft_strjoin(new_cmd, " ");
	else if (is_token(cmd[i]) && ft_isalnum(cmd[i + 1]))
		new_cmd = ft_strjoin(new_cmd, " ");
	else if (is_token(cmd[i]) && (cmd[i + 1] == '\"' || cmd[i + 1] == '\'')
		&& !nb_quote_before_token(cmd, i, cmd[i + 1]))
		new_cmd = ft_strjoin(new_cmd, " ");
	else if ((cmd[i] == '\"' || cmd[i] == '\"') && is_token(cmd[i + 1])
		&& !nb_quote_before_token(cmd, i + 1, cmd[i]))
		new_cmd = ft_strjoin(new_cmd, " ");
	*ad_cmd = new_cmd;
}
