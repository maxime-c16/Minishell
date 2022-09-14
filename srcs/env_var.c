/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:50:26 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/14 13:21:46 by yschecro         ###   ########.fr       */
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

char	*change_var(char *token, char *key, int len)
{
	char	*out;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = get_value(key);
	out = malloc(ft_strlen(token) - ft_strlen(key) + ft_strlen(get_value(key)));
	if (!out)
		hasta_la_vista(1);
	while (token[j] != '$')
		out[i++] = token[j++];
	if (value)
		out = ft_strjoin(out, value);
	i += ft_strlen(value);
	j += len + 1;
	while (token[j])
		out[i++] = token[j++];
	out[i] = 0;
	return (out);
}

char	*insert(char *token)
{
	int		i;
	int		len;
	char	*out;
	char	*key;

	i = 0;
	len = 0;
	while (token[i] != '$' && token[i])
		i++;
	i++;
	while (!ft_strchr(EXPAND_CHAR, token[i + len]) && token[i])
		len++;
	key = get_key(token, i, len);
	out = change_var(token, key, len);
	return (free(token), out);
}

char	**expand(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		while (ft_strchr(token[i], '$'))
		{
			token[i] = insert(token[i]);
		}
		i++;
	}
	token[i] = NULL;
	return (token);
}
