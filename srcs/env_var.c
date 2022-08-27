/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/08/27 18:10:54 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next_word(char *str)
{
	if (ft_strlen(str) > 1)
		return (str + 1);
	return (NULL);
}

char **expand(char **token)
{
	int	i;
	char	*new_word;

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '$')
		{
			if (ft_strlen(token[i]) <= 1)
				return (token);
			new_word = get_value(get_next_word(token[i]));
			free(token[i]);
			if (!new_word)
			{
//				dprintf(2, "\n\nnull found\n");
				token[i][0] = 0;
			}
			else
				token[i] = new_word;
		}
		i++;
	}
	return (token);
}
