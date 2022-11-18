/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd_better_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:04 by yschecro          #+#    #+#             */
/*   Updated: 2022/11/18 17:57:29 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	dfill_utils(char **cmd, t_help *help, char c)
{
	while ((*cmd)[help->i + help->j] && (*cmd)[help->i + help->j] != c
			&& (*cmd)[help->i + help->j])
	{
		if (ft_is_quote((*cmd)[help->i + help->j]))
			ft_pass_quote_sp((*cmd), help->i, &help->j);
		if (!(*cmd)[help->i + help->j])
			break ;
		++help->j;
	}

}

char	**ft_dfill(char ***output, char *cmd, char c)
{
	t_help	help;

	help.i = 0;
	help.p = 0;
	while (cmd[help.i])
	{
		if (cmd[help.i] != c)
		{
			help.j = 0;
			dfill_utils(&cmd, &help, c);
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
