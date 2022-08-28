/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 12:06:41 by mcauchy          ###   ########.fr       */
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

int	ft_strlen_tab(char **tab)
{
	int	i;

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
	char	*line;

	(void)ac;
	(void)av;
	using_history();
	while (42)
	{
		//sig_choice(0);
		line = readline(C_RED"Minishell"C_RESET"$> ");
		refacto_token_space(line);
		if (!line)
			hasta_la_vista(0);
		add_history(line);
		parsing(line, env);
		ft_exec();
		hasta_la_vista(1);
	}
	return (0);
}
