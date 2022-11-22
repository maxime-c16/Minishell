/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/11/22 01:36:50 by yschecro         ###   ########.fr       */
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
	out = malloc(len + 2);
	if (!out)
		hasta_la_vista(1);
	if (token[i] == '?')
	{
		out[0] = '?';
		j++;
	}
	else
	{
		while (j < len)
		{
			out[j] = token[i + j];
			j++;
		}
	}
	out[j] = 0;
	return (out);
}

char	*lcd_strjoin(char *s1, char *s2)
{
	char	*output;
	int		i;
	int		j;

	output = ft_calloc(sizeof(char), ((ft_strlen(s1) + ft_strlen(s2) + 2)));
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
	out = ft_calloc(sizeof(char), lenght + 2);
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
		out = ft_strjoin_char(out, token[j++]);
		i++;
	}
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
	if (!ft_strlen(key))
		return (free(key), free(token), ft_strdup("$"));
	if (*(token + 1) == '?')
		return (free(key), free(token), ft_itoa(g_value));
	if (*(token + 1) == '<' || *(token + 1) == '>')
		return (free(key), free(token), ft_strdup(""));
	out = change_var(token, key, len, i);
	free(key);
	return (free(token), out);
}
