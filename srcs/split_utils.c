/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:09:38 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/27 16:10:16 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_char(char **cmd, int *i, int *len, char c)
{
	if ((*cmd)[*i] == c)
	{
		(*i)++;
		(*len)++;
		while ((*cmd)[*i] != c && (*cmd)[*i])
			(*i)++;
		(*i)++;
	}
}

static void	skip_space(char **cmd, int *i, int *len)
{
	if (!is_space((*cmd)[*i]))
	{
		(*i)++;
		(*len)++;
		while (!is_space((*cmd)[*i]) && (*cmd)[*i])
			(*i)++;
		(*i)++;
	}
}

int	count_word(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		skip_char(&cmd, &i, &len, '\'');
		skip_char(&cmd, &i, &len, '\"');
		skip_space(&cmd, &i, &len);
		while (cmd[i] && is_space(cmd[i]))
			i++;
	}
	return(len);
}
