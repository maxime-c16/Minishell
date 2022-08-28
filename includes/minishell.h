/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:26:45 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/28 11:42:28 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
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
char	**ft_dup_tab(char **str);

//free.c

void	hasta_la_vista(int flag);
void	ft_free_tab(char **tab);
void	ft_print_lst(void);

//singleton.c

t_list	*_lst(void);
t_data	*_data(void);


//env_var.c

char **expand(char **token);

//env_manipulating.c

char *lcd_strcmp(char *s1, char *s2);
char	*get_value(char *key);

//env_parsing.c

int		test_env(char **env);
char	*ft_strndup(char *str, int n);
int		split_env(char **ev);
int		len_env(char **env);

//parsing.c

int		parsing(char *cmd, char **env);

//insertion.c

void	ft_insertion(char **token, int *i, t_list **lst, char **env);
void	init_new_token(char **env);

//data_struct.c

void	ft_parse_and_insert(char **token, char **env);
int		ft_count_cmd(char **token, int i);

//exec.c

void	ft_exec(void);
void	ft_exec_cmd(t_list *lst, char **cmd, int i);

//exec_utils.c

void	multi_cmd_exec(void);
void	one_builtin_exec(void);

//paths.c

char	*ft_path(char **full_path, char *cmd);

//init.c

void	init_pid(void);
void	init_fd(void);

//utils.c

int		ft_lst_size_without_pipe(void);
void	ft_waitpid(void);
void	ft_error(char *str);
void	ft_dup2(int in, int out);
void	init_heredocs(t_list **lst);

//redirections.c

void	ft_redirections(t_list *lst);
char	**ft_clean_redirection(char **cmd);

//redirections_utils.c

char	**ft_clean_redir_cmd(char **cmd);
int		ft_check_redir(char **cmd);
void	ft_exec_redir(t_list **lst, char ***ad_cmd);

//utils2.c

int		ft_lst_heredocs(void);
void	unlink_hd(void);

//heredocs.c

void	limit_heredocs(void);
void	close_hd(void);

//heredocs_utils.c

void	write_hd(void);
void	ft_dup_heredocs(t_list *tmp);

//builtins.c

int	is_builtin(char *cmd);

//builtins_exec.c

void	echo_cmd(char **cmd);
void	exit_cmd(void);
void	pwd_cmd(void);

//signals.c

void	sig_choice(int sig);

#endif
