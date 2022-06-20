/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:26:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/06/20 23:14:48 by mcauchy          ###   ########.fr       */
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

//free.c

void	hasta_la_vista(void);
void	ft_free_tab(char **tab);

//singleton.c

t_list	*_data(void);

//parsing.c

t_list	*parsing(char *cmd);

//redirections.c

t_list	*ft_redirections(t_list *lst);

#endif
