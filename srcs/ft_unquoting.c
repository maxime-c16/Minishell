/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unquoting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:58:44 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/22 03:40:33 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	check_quote(int is_in_quote, char c, int *i)
{
	if (c == '\'' && is_in_quote == 1)
		return ((*i)++, 0);
	if (c == '\"' && is_in_quote == 1)
		return (1);
	if (c == '\'' && is_in_quote == 0)
		return ((*i)++, 1);
	if (c == '\"' && is_in_quote == 0)
		return ((*i)++, 2);
	if (c == '\'' && is_in_quote == 2)
		return (2);
	if (c == '\"' && is_in_quote == 2)
		return ((*i)++, 0);
	return (is_in_quote);
}
*/
static int	unquote_utils(int is_in_quote, char c)
{
	if (c == '\'' && is_in_quote == 1)
		return (0);
	if (c == '\"' && is_in_quote == 1)
		return (1);
	if (c == '\'' && is_in_quote == 0)
		return (1);
	if (c == '\"' && is_in_quote == 0)
		return (2);
	if (c == '\'' && is_in_quote == 2)
		return (2);
	if (c == '\"' && is_in_quote == 2)
		return (0);
	return (is_in_quote);
}

static char	*unquote_line(char	*str)
{
	int		i;
	int		is_in_quote;
	char	*out;

	is_in_quote = 0;
	i = 0;
	out = ft_calloc(1, 1);
	if (!out)
		hasta_la_vista(0);
	while (str[i])
	{
		is_in_quote = unquote_utils(is_in_quote, str[i]);
		if (!str[i])
			break ;
		out = ft_unquote_join(out, str[i], is_in_quote);
		i++;
	}
	if (is_in_quote == 1 || is_in_quote == 2)
		return (free(str), free(out), ft_unquote_error(), NULL);
	return (free(str), out);
}

static char	**unquote_cmd(char **cmd)
{
	char	**out;
	int		i;

	i = 0;
	out = ft_calloc(sizeof(char *), (ft_tablen(cmd) + 1));
	if (!out)
		hasta_la_vista(0);
	while (cmd[i])
	{
		out[i] = unquote_line(cmd[i]);
		if (!out[i])
			return (ft_free_tab(out), free(cmd), NULL);
		i++;
	}
	free(cmd);
	return (out);
}

void	ft_unquoting(void)
{
	t_list	*lst;

	lst = _lst();
	while (lst)
	{
		if (lst->token && lst->token->cmd)
			lst->token->cmd = unquote_cmd(lst->token->cmd);
		lst = lst->next;
	}
}
