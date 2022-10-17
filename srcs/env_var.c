/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/10/14 17:41:23 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next_word(char *str)
{
	if (ft_strlen(str) > 1)
		return (str + 1);
	return (NULL);
}

char	*get_key(char *token, int i, int len)
{
	char	*out;
	int		j;

	j = 0;
	out = malloc(len + 1);
	if (!out)
		hasta_la_vista(1);
	while (j < len)
	{
		out[j] = token[i + j];
		j++;
	}
	out[j] = 0;
	return (out);
}

char	*lcd_strjoin(char *s1, char *s2)
{
	char	*output;
	int		i;
	int		j;

	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		hasta_la_vista(1);
	i = 0;
	j = 0;
	while (s1[i])
		output[j++] = s1[i++];
	i = 0;
	while (s2[i])
		output[j++] = s2[i++];
	output[j] = '\0';
	return (free(s1), output);
}

char	*change_var(char *token, char *key, int len, int start)
{
	char	*out;
	char	*value;
	int		lenght;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = get_value(key);
	lenght = ft_strlen(token) - ft_strlen(key) + ft_strlen(value);
	out = ft_calloc(sizeof(char), lenght);
	if (!out)
		hasta_la_vista(0);
	while (i < start - 1 && token[j])
		out[i++] = token[j++];
	if (value)
		out = lcd_strjoin(out, value);
	i = start + ft_strlen(value) - 1;
	j += len + 1;
	while (i < lenght && token[j])
	{
		out[i] = token[j];
		i++;
		j++;
	}
	out[i] = 0;
	return (out);
}

char	*insert(char *token, int i)
{
	int		len;
	char	*out;
	char	*key;

	len = 0;
	i++;
	while (!ft_strchr(EXPAND_CHAR, token[i + len]) && token[i])
		len++;
	key = get_key(token, i, len);
	if (*(token + 1) == '?')
		return (free(token), ft_itoa(g_value));
	out = change_var(token, key, len, i);
	free(key);
	return (free(token), out);
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
		if (tmp[*i][*j] == '$')
			tmp[*i] = insert(tmp[*i], *j);
		(*j)++;
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
