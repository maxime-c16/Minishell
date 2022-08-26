/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/08/26 15:25:20 by yschecro         ###   ########.fr       */
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
//		printf("old token: _%s_\n", token[i]);
		if (token[i][0] == '$')
		{
			if (ft_strlen(token[i]) <= 1)
				return (NULL);
//			dprintf(2, "in condition\n");
			new_word = get_value(get_next_word(token[i]));
//			dprintf(2, "new word = :%s\n", new_word);
			free(token[i]);
			token[i] = new_word;
//			printf("new token: %s\n", token[i]);
		}
		i++;
	}
	return (token);
}
