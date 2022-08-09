/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/09 12:15:53 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_dup_tab(char **str)
{
	char	**tab;
	int		i;

	i = 0;
	while (str[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		tab[i] = ft_strdup(str[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}


int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		dprintf(2, "%d %s\n", i, tab[i]);
		i++;
	}
}

void	ft_print_lst(void)
{
	t_list	*lst;
	int		i;

	lst = _lst();
	i = 0;
	while (lst)
	{
		dprintf(2, "------------nouveau maillon %d ----------\n", i);
		ft_print_tab(lst->token->cmd);
		lst = lst->next;
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	t_list	*lst;

	lst = _lst();
	line = readline("Minishell$> ");
	while (line && ft_strncmp(line, "exit", 4) != 0)
	{
		parsing(line, env);
		ft_exec();
		hasta_la_vista();
		line = readline("Minishell$> ");
	}
	return (0);
}

