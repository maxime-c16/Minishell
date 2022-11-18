/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:09:38 by yschecro          #+#    #+#             */
/*   Updated: 2022/11/18 17:56:45 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pass_quote(char *cmd, int *j)
{
	char	c;

	c = ft_is_quote(cmd[(*j)]);
	(*j)++;
	while (cmd[(*j)] != c && cmd[(*j)])
		(*j)++;
}

int	count_utils(char *cmd, int *i)
{
	while (cmd[*i] && !is_space(cmd[*i]))
	{
		if (ft_is_quote(cmd[*i]))
		{
			ft_pass_quote(cmd, i);
			if (!cmd[*i])
				break ;
			++(*i);
		}
		else
			++(*i);
	}
	return (1);
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
			count_utils(cmd, &i);
			total++;
		}
		else
			++i;
	}
	return (total);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}

void	ft_pass_quote_sp(char *cmd, int i, int *j)
{
	char	c;

	c = ft_is_quote(cmd[i + (*j)]);
	(*j)++;
	while (cmd[i + (*j)] != c && cmd[i + (*j)])
		(*j)++;
}

