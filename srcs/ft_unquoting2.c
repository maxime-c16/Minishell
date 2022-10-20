/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unquoting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:00:06 by mcauchy           #+#    #+#             */
/*   Updated: 2022/10/19 12:17:38 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unquote_error(char *cmd, int i)
{
	if (cmd[i] == '\0')
	{
		printf("minishell: error: quote not closed\n");
		_data()->error = 1;
	}
}

char	find_next_quote(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '"')
			return (cmd[i]);
		else if (cmd[i] == '\'')
			return (cmd[i]);
		i++;
	}
	return ('\0');
}
