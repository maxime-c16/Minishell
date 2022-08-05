/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:26:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/05 15:33:36 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 2
# define PIPE 1
# define REDIR_SIMPLE 2
# define REDIR_DOUBLE 3
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define FD_STDOUT 1
# define FD_STDIN 0
# define FD_STDERR 2

char	**ft_split(char const *s, char c);

//main.c

void	ft_print_tab(char **tab);
void	ft_print_lst(t_list *lst);

//free.c

void	hasta_la_vista(void);
void	ft_free_tab(char **tab);
void	ft_free_lst(t_list *lst);

//singleton.c

t_list	*_lst(void);
t_data	*_data(void);

//parsing.c

void	parsing(char *cmd, char **env);

//insertion.c

void	ft_insertion(char **token, int *i, t_list **lst, char **env);
void	init_new_token(char **env);

//data_struct.c

void	ft_parse_and_insert(char **token, char **env);
int		ft_count_cmd(char **token, int i);

//exec.c

void	ft_exec(void);

//paths.c

char	*ft_path(char **full_path, char *cmd);

// init.c

void	init_pid(void);

#endif
