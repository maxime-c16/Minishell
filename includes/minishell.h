/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:26:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/17 21:11:18 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE 1
# define REDIR_SIMPLE 2
# define REDIR_DOUBLE 3

typedef	struct s_token
{
	char	**str;
	int		type;
}	t_token;

typedef struct s_data
{
	t_token			*token;
	struct s_data	*next;
}	t_data;

//free.c

void	hasta_la_vista(void);

//singleton.c

t_data	*_data(void);

//parsing.c

void	parsing(char *cmd);

#endif
