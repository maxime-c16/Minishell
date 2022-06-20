/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/20 22:36:08 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_print_lst(t_list *lst)
{
	while (lst->token->cmd)
	{
		ft_print_tab(lst->token->cmd);
		lst = lst->next;
	}
}

int	main(int ac, char **av, char **env)
{

	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	t_list	*lst;

	lst = _data();
	line = readline("Minishell$> ");
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		lst = parsing(line);
		line = readline("Minishell$> ");
	}
	return (0);
}

