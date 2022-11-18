/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd_better_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:04 by yschecro          #+#    #+#             */
/*   Updated: 2022/11/18 14:09:59 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}

void	ft_pass_quote(char *cmd, int *j)
{
	char	c;

	c = ft_is_quote(cmd[(*j)]);
	(*j)++;
	while (cmd[(*j)] != c && cmd[(*j)])
		(*j)++;
}

int	ft_count(char *cmd)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (cmd[i])
	{
		if (cmd[i] && !is_space(cmd[i]))
		{
			while (cmd[i] && !is_space(cmd[i]))
			{
				if (ft_is_quote(cmd[i]))
				{
					ft_pass_quote(cmd, &i);
					if (!cmd[i])
						break;
					++i;
				}
				else
					++i;
			}
			total++;
		}
		else
			++i;
	}
	return (total);
}

static void	ft_pass_quote_sp(char *cmd, int i, int *j)
{
	char	c;

	c = ft_is_quote(cmd[i + (*j)]);
	(*j)++;
	while (cmd[i + (*j)] != c && cmd[i + (*j)])
		(*j)++;
}

static char	*ft_fill(char *s, int size, int *index)
{
	char	*output;
	int		i;

	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (i < size)
	{
		output[i] = s[*index];
		i++;
		*index += 1;
	}
	output[i] = 0;
	return (output);
}

static char	**ft_dfill(char ***output, char *cmd, char c)
{
	t_help	help;

	help.i = 0;
	help.p = 0;
	while (cmd[help.i])
	{
		if (cmd[help.i] != c)
		{
			help.j = 0;
			while (cmd[help.i + help.j] && cmd[help.i + help.j] != c && cmd[help.i + help.j])
			{
				if (ft_is_quote(cmd[help.i + help.j]))
					ft_pass_quote_sp(cmd, help.i, &help.j);
				if (!cmd[help.i + help.j])
					break ;
				++help.j;
			}
			(*output)[help.p] = ft_fill(cmd, help.j, &help.i);
			if (!(*output))
				return (ft_free_tab((*output)), NULL);
			help.p++;
		}
		else
			help.i++;
	}
	(*output)[help.p] = NULL;
	return (free(cmd), (*output));
}

static int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

char	**lcd_split(char *cmd)
{
	char	**output;

	if (!cmd || ft_is_space(cmd) == 1)
		return (free(cmd), NULL);
	output = malloc(sizeof(char *) *(ft_count(cmd) + 1));
	if (!output)
		return (free(cmd), NULL);
	return (ft_dfill(&output, cmd, ' '));
}
