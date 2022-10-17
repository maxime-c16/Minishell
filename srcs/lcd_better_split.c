/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd_better_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:04 by yschecro          #+#    #+#             */
/*   Updated: 2022/10/17 14:02:46 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_quote(char **cmd, char quote, char **out, int *j)
{
	int	i;

	i = 0;
	if ((*cmd)[i] == quote)
	{
		i++;
		while ((*cmd)[i] != quote && (*cmd)[i])
			i++;
		out[*j] = ft_strndup(*cmd, i + 1);
		(*j)++;
		(*cmd) += i + 1;
	}
}

void	split_token(char **cmd, char **out, int *j)
{
	if (is_token(**cmd))
	{
		out[*j] = ft_calloc(1, 3);
		if (!out)
			hasta_la_vista(1);
		out[*j][0] = **cmd;
		(*cmd)++;
		if (is_token(**cmd))
		{
			out[*j][1] = **cmd;
			(*cmd)++;
		}
		(*j)++;
	}
}

void	split_space(char **cmd)
{
	if (is_space(**cmd) && **cmd)
	{
		while (is_space(**cmd))
			(*cmd)++;
	}
}

void	split_char(char **cmd, char **out, int *j)
{
	int	i;

	i = 0;
	while (!is_token((*cmd)[i]) && (*cmd)[i] && \
			!is_space((*cmd)[i]) && (*cmd)[i] != '\'' && (*cmd)[i] != '\"')
	{
		i++;
	}
	if (i)
	{
		out[*j] = ft_strndup(*cmd, i);
		(*j)++;
		(*cmd) += i;
	}
}

char	**lcd_split(char *cmd)
{
	char	**out;
	int		j;
	int		len;

	len = count_word(cmd);
	out = malloc(sizeof(char *) * (len + 2));
	if (!out)
		return (out);
	j = 0;
	while (j < len && *cmd)
	{
		split_quote(&cmd, '\'', out, &j);
		split_quote(&cmd, '\"', out, &j);
		split_token(&cmd, out, &j);
		split_space(&cmd);
		split_char(&cmd, out, &j);
	}
	out[j] = NULL;
	return (out);
}
