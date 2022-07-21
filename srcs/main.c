/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/07/21 14:11:23 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_print_lst(t_list *lst)
{
	while (lst)
	{
		printf("------------nouveau maillon------------\n");
		ft_print_tab(lst->token->cmd);
		lst = lst->next;
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
		lst = parsing(line, env);
		//ft_print_lst(lst);
		ft_exec();
		hasta_la_vista();
		line = readline("Minishell$> ");
	}
	return (0);
}

