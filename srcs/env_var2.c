/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:54:05 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 15:21:44 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expand_utils_utils(char ***tmp, int *i, int *j)
{
	if ((*tmp)[*i][*j] == '$')
		(*tmp)[*i] = insert((*tmp)[*i], *j);
	if (!(*tmp)[*i] || !(*tmp)[*i][*j])
		return (0);
	(*j)++;
	if (!(*tmp)[*i] || !(*tmp)[*i][*j])
		return (0);
	return (1);
}

static void	expand_utils(char ***token, int *i, int *j)
{
	int		is_in_quote;
	char	**tmp;

	tmp = *token;
	is_in_quote = 0;
	while (tmp[*i][*j])
	{
		if (tmp[*i][*j] == '\"' && is_in_quote == 0)
			is_in_quote = 1;
		else if (tmp[*i][*j] == '\"' && is_in_quote == 1)
			is_in_quote = 0;
		if (tmp[*i][*j] == '\'')
		{
			(*j)++;
			while (tmp[*i][*j] != '\'' && tmp[*i][*j])
			{
				if (tmp[*i][*j] == '$' && is_in_quote == 1)
					tmp[*i] = insert(tmp[*i], *j);
				(*j)++;
			}
		}
		if (!expand_utils_utils(&tmp, i, j))
			return ;
	}
}

char	**expand(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		j = 0;
		expand_utils(&token, &i, &j);
		i++;
	}
	token[i] = NULL;
	return (token);
}
