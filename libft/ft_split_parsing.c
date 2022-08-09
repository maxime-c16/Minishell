/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 19:41:07 by maximecauch       #+#    #+#             */
/*   Updated: 2022/08/09 19:29:40 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	word_count(char const *s, char c)
{
	int		wd;
	int		i;

	i = 0;
	wd = 0;
	if (s[0] != c)
		wd++;
	while (s[++i])
	{
		if (s[i] != c && s[i - 1] == c)
			wd++;
		else if (s[i] == '"')
		{
			wd++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++;
		}
		else if (s[i] == '\'')
		{
			wd++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
	}
	return (wd);
}

static char **check_cmd(char const *s, int *i, char **tab, int *ind)
{
	int		start;

	start = *i;
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] != '"')
			(*i)++;
		(*i)++;
		tab[*ind] = ft_substr(s, start, (*i) - start);
		(*ind)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'')
			(*i)++;
		(*i)++;
		tab[*ind] = ft_substr(s, start, (*i) - start);
		(*ind)++;
	}
	else
	{
		while (s[*i] && s[*i] != ' ')
			(*i)++;
		tab[*ind] = ft_substr(s, start, (*i) - start);
		(*ind)++;
	}
	tab[*ind] = NULL;
	return (tab);
}

char	**ft_split_parsing(char const *s, char c)
{
	int		i;
	int		ind;
	char	**tab;

	i = 0;
	ind = 0;
	tab = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			tab = check_cmd(s, &i, tab, &ind);
		i++;
	}
	return (tab);
}
