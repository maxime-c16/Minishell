/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd_better_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:04 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/28 19:06:58 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' \
			|| c == '\f')
		return (1);
	return (0);
}


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
		out[*j] = ft_strndup((*cmd), 1);
		(*j)++;
		(*cmd)++;
	}
}

void	split_space(char **cmd)
{
	if (is_space(**cmd))
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
	out = malloc(sizeof(char *) * (len + 1));
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
