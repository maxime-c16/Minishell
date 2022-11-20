/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:39:58 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/20 16:36:03 by mcauchy          ###   ########.fr       */
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

static char	*ft_prompt_color(void)
{
	if (g_value == 0)
		return (C_GREEN"Minishell"C_RESET"$> ");
	else
		return (C_RED"Minishell"C_RESET"$> ");
}

static void	main_help(void)
{
	_data()->error = 0;
	_data()->save_in = dup(0);
	_data()->save_out = dup(1);
	sig_choice(1);
}

static void	super_main_helper(char **env)
{
	sig_choice(0);
	using_history();
	if (!test_env(env) || !split_env(env))
		hasta_la_vista(1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	super_main_helper(env);
	while (42)
	{
		main_help();
		line = readline(ft_prompt_color());
		if (!line || !isatty(0))
			hasta_la_vista(0);
		if (!line[0] || skip_spaces(line) == -1)
		{
			close_main(line);
			continue ;
		}
		add_history(line);
		parsing(line);
		if (_data()->error)
			continue ;
		ft_exec();
		hasta_la_vista(1);
	}
	return (0);
}
