/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/01 10:21:06 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next_word(char *str)
{
	if (ft_strlen(str) > 1)
		return (str + 1);
	return (NULL);
}

char	**expand(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '$')
		{
			if (ft_strlen(token[i]) <= 1)
				return (token);
			free(token[i]);
			token[i] = get_value(get_next_word(token[i]));
		}
		i++;
	}
	return (token);
}
