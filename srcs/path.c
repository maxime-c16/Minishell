/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:18:34 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 15:53:49 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char	**ft_cat_path_with_cmd(char **path, char *cmd)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_tablen(path) + 1));
	if (!tab)
		hasta_la_vista(0);
	while (path[i])
	{
		tab[i] = ft_strjoin(path[i], "/");
		tab[i] = ft_strjoin(tab[i], cmd);
		i++;
	}
	tab[i] = NULL;
	ft_free_tab(path);
	return (tab);
}

char	*ft_path(char **full_path, char *cmd)
{
	char	**path;
	char	**tmp_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	while (full_path[i])
	{
		j = 0;
		if (ft_strncmp(full_path[i], "PATH=", 5) == 0)
		{
			path = ft_split(ft_strdup(full_path[i] + 5), ':');
			tmp_path = ft_cat_path_with_cmd(path, cmd);
			while (tmp_path[j])
			{
				if (!access(tmp_path[j], F_OK))
					return (tmp_path[j]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
