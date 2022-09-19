/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/04 01:40:38 by yschecro         ###   ########.fr       */
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

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '$')
		{
			if (ft_strlen(token[i]) <= 1)
				return (token);
			free(token[i]);
			dprintf(2, "token avant get_value = %s\n", token[i]);
			token[i] = get_value(get_next_word(token[i]));
			dprintf(2, "token apres get value= %s\n", token[i]);
		}
		i++;
	}
	return (token);
}
