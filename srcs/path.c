/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:18:34 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 15:24:22 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_cat_path_with_cmd(char **path, char *cmd)
{
	char	**tab;
	char	*temp;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_tablen(path) + 1));
	if (!tab)
		hasta_la_vista(0);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		tab[i] = temp;
		temp = ft_strjoin(tab[i], cmd);
		free(tab[i]);
		tab[i] = temp;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static void	path_help(char **free1, char **free2)
{
	ft_free_tab(free1);
	ft_free_tab(free2);
}

char	**ft_path(char **full_path, char *cmd, int *j)
{
	char	**path;
	char	**tmp_path;
	char	*temp;
	int		i;

	i = -1;
	while (full_path[++i])
	{
		(*j) = 0;
		temp = (ft_strdup(full_path[i] + 5));
		if (ft_strncmp(full_path[i], "PATH=", 5) == 0)
		{
			path = ft_split(temp, ':');
			tmp_path = ft_cat_path_with_cmd(path, cmd);
			while (tmp_path[(*j)])
			{
				if (!access(tmp_path[(*j)], F_OK))
					return (free(temp), tmp_path);
				(*j)++;
			}
			path_help(path, tmp_path);
		}
		free(temp);
	}
	return (NULL);
}
