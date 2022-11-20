/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unquoting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:00:06 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/20 20:05:28 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unquote_error(void)
{
	printf("minishell: error: quote not closed\n");
	_data()->error = 1;
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

char	*ft_unquote_join(char *str, char c, int is_in_quote)
{
	if (c == '\'')
	{
		if (is_in_quote == 1 || !is_in_quote)
			return (str);
		else
			return (ft_strjoin_char(str, c));
	}
	else if (c == '\"')
	{
		if (is_in_quote == 2 || !is_in_quote)
			return (str);
		else
			return (ft_strjoin_char(str, c));
	}
	else
		return (ft_strjoin_char(str, c));
}
