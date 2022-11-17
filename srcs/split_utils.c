/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:09:38 by yschecro          #+#    #+#             */
/*   Updated: 2022/11/17 22:02:09 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_allowed(char c)
{
	if (c == '\'' || c == '\"' || is_space(c) || is_token(c) || !c)
		return (0);
	return (1);
}

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

static void	skip_word(char **cmd, int *i, int *len)
{
	if (is_allowed((*cmd)[*i]))
	{
		(*i)++;
		(*len)++;
		while (is_allowed(((*cmd)[*i])))
			(*i)++;
		if (!(*cmd)[*i])
			return ;
		(*i)++;
	}
}

static void	skip_token(char **cmd, int *i, int *len)
{
	if (is_token((*cmd)[*i]))
	{
		(*i)++;
		(*len)++;
		while (is_token(((*cmd)[*i])))
			(*i)++;
		if (!(*cmd)[*i])
			return ;
		(*i)++;
	}
}

int	count_word(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		skip_char(&cmd, &i, &len, '\'');
		skip_char(&cmd, &i, &len, '\"');
		skip_token(&cmd, &i, &len);
		skip_word(&cmd, &i, &len);
		while (cmd[i] && is_space(cmd[i]))
			i++;
	}
	return (len);
}
