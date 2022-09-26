/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/19 23:34:05 by yschecro         ###   ########.fr       */
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
	out= malloc(len + 1);
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

	if (!s1)
		return ((char *)s2);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (NULL);
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
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = get_value(key);
	out = malloc(ft_strlen(token) - ft_strlen(key) + ft_strlen(get_value(key)) + 1);
	if (!out)
		hasta_la_vista(1);
	while (i < start - 1)
		out[i++] = token[j++];
	if (value)
		out = lcd_strjoin(out, value);
	i += ft_strlen(value);
	j += len + 1;
	while (token[j])
		out[i++] = token[j++];
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
//	dprintf(2, "key at index i = %s\n", token + i);
	key = get_key(token, i, len);
//	dprintf(2, "getkey = %s\n", key);
	out = change_var(token, key, len, i);
	return (free(token), out);
}

char	**expand(char **token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (token[i])
	{
//		dprintf(2, "token before expand = %s\n", token[i]);
		j = 0;
		while (token[i][j])
		{
//			dprintf(2, "first loop			char == %c\n", token[i][j]);
			if (token[i][j] == 39)
			{
//				dprintf(2, "quote found\n");
				j++;
				while (token[i][j] != 39 && token[i][j])
					j++;
//				dprintf(2, "quote skipped\n");
			}
			if (token[i][j] == '$')
			{
//				dprintf(2, "dollar found\n");
				token[i] = insert(token[i], j);
			}
			j++;
		}
		dprintf(2, "token after expand = %s\n", token[i]);
		i++;
	}
	token[i] = NULL;
	return (token);
}
