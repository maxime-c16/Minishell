/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/22 13:25:51 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Parcourir la liste chainee et remplir une autre liste chaine qui contient les commandes dans un char** sans pipe ni chevron
//+tableau de pid dans cette liste qui sera malloc au nombre de commande
//+tableau de pipe malloc a (nb commande - 1) * 2
//il faut pipe chaque pipe adjacente donc pipe(params->fd + i * 2);
//Parcourir cette nouvelle liste chainee et fork a chaque fois,
//si c la premiere commande
//on dup les bon infile + outfile
//si c la derniere commande on pipe les bon fd + outfile
//si c des commandes entre les deux on pipe les bon fd + outfile
//close certains fd
//ensuite execve

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
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		lst = parsing(line, env);
		//ft_print_lst(lst);
		ft_exec();
		line = readline("Minishell$> ");
	}
	return (0);
}

