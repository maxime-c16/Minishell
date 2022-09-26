/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd_better_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:04 by yschecro          #+#    #+#             */
/*   Updated: 2022/09/26 18:29:57 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
   static char	*ft_strndup(char *str, int n)
   {
   int		i;
   char	*out;

   i = 0;
   out	= malloc(ft_strlen(str) + 1);
   if (!out)
   return (NULL);
   while (str[i] && i < n)
   {
   out[i] = str[i];
   i++;
   }
   out[i] = 0;
   return (out);
   }
   */
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' \
			|| c == '\f')
		return (1);
	return (0);
}

int	count_word(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			len++;
			while (cmd[i] != '\'' && cmd[i])
				i++;
			i++;
		}
		if (cmd[i] == '\"')
		{
			i++;
			len++;
			while (cmd[i] != '\"' && cmd[i])
				i++;
			i++;
		}
		if (!is_space(cmd[i]))
		{
			i++;
			len++;
			while (!is_space(cmd[i]) && cmd[i])
				i++;
			i++;
		}
		while (is_space(cmd[i]))
			i++;
	}
	return(len);
}

char	**lcd_split(char *cmd)
{
	char	**out;
	int		i;
	int		j;
	int		len;

	len = count_word(cmd);
	dprintf(2, "len = %d\n", len);
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (out);
	i = 0;
	j = 0;
	while (j < len && *cmd)
	{
		dprintf(2, "i cant quit and cmd[i] = %c\n", cmd[i]);
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i])
				i++;
			out[j] = ft_strndup(cmd, i + 1);
			j++;
			cmd += i + 1;
			i = 0;
			continue ;
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i])
				i++;
			out[j] = ft_strndup(cmd, i + 1);
			j++;
			cmd += i + 1;
			i = 0;
			continue ;
		}
		if (is_token(cmd[i]))
		{
			out[j] = ft_strndup(cmd, i);
			j++;
			i++;
			cmd++;
			i = 0;
			continue ;

		}
		if (is_space(cmd[i]))
		{
			while (is_space(*cmd))
				cmd++;
		}
		//		if (!is_token(cmd[i]) && cmd[i] && !is_space(cmd[i]) && cmd[i] \
 //		!= '\'' && cmd[i] != '\"')
			//		{
		while (!is_token(cmd[i]) && cmd[i] && !is_space(cmd[i]) && cmd[i] != '\'' && cmd[i] != '\"')
		{
			i++;
		}
		if (i)
		{
			out[j] = ft_strndup(cmd, i);
			j++;
			cmd += i;	
			i = 0;
		}
		//		}
	}
	out[j] = NULL;
	return (out);
}
