/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:39:21 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/17 16:12:42 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_value = 130;
	}
	else if (sig == SIGQUIT)
		g_value = 131;
}

static void	hd_sig_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	open("/dev/stdin", O_RDWR);
	g_value = 160903;
}

void	sig_choice(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else if (sig == 2)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 3)
	{
		signal(SIGINT, hd_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
