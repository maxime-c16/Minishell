/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/16 18:12:24 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_value = 0;

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

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return ;
	while (tab[i])
	{
		dprintf(2, "%dth %s\n", i, tab[i]);
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
		dprintf(2, "------------| maillon %d |----------\n", i);
		ft_print_tab(lst->token->cmd);
		lst = lst->next;
		i++;
	}
}

static char	*ft_prompt_color(void)
{
	if (g_value == 0)
		return (C_GREEN"Minishell"C_RESET"$> ");
	else
		return (C_RED"Minishell"C_RESET"$> ");
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	sig_choice(0);
	using_history();
	if (!test_env(env) || !split_env(env))
		hasta_la_vista(1);
	while (42)
	{
		_data()->error = 0;
		_data()->save_in = dup(0);
		_data()->save_out = dup(1);
		sig_choice(1);
		line = readline(ft_prompt_color());
		if (!line)
			hasta_la_vista(0);
		if (!line[0] || skip_spaces(line) == -1)
		{
			free(line);
			continue ;
		}
		add_history(line);
		parsing(line);
		if (_data()->error)
			continue ;
		dprintf(2, "before exec\n");
		ft_print_lst();
		ft_exec();
		hasta_la_vista(1);
	}
	return (0);
}
