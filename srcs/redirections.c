/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:07:31 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/27 15:05:28 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_redirection_right(char **cmd, int i)
{
	int	fd2;

	fd2 = 0;
	if (cmd[i + 1] == NULL)
		ft_error("minishell: syntax error near unexpected token `newline'\
			\n");
	else if (cmd[i + 1][0] == '<' || cmd[i + 1][0] == '>')
		ft_error("minishell: syntax error near unexpected token `newline'\
			\n");
	else if (cmd[i + 1][0] == '|')
		ft_error("minishell: syntax error near unexpected token `newline'\
			\n");
	else
	{
		fd2 = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd2 == -1)
			ft_error("minishell: error while opening file\n");
		else
		{
			dup2(fd2, FD_STDOUT);
			close(fd2);
		}
	}
}

static void	ft_redirection_left(char **cmd, int i)
{
	int	fd2;

	fd2 = 0;
	if (cmd[i + 1] == NULL)
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else if (cmd[i + 1][0] == '<' || cmd[i + 1][0] == '>')
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else if (cmd[i + 1][0] == '|')
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else
	{
		fd2 = open(cmd[i + 1], O_RDONLY);
		if (fd2 == -1)
			ft_error("minishell: error while opening file\n");
		else
		{
			dup2(fd2, FD_STDIN);
			close(fd2);
		}
	}
}

static void	ft_redirection_right_right(char **cmd, int i)
{
	int	fd2;

	fd2 = 0;
	if (cmd[i + 1] == NULL)
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else if (cmd[i + 1][0] == '<' || cmd[i + 1][0] == '>')
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else if (cmd[i + 1][0] == '|')
		ft_error("minishell: syntax error near unexpected token `newline'\n");
	else
	{
		fd2 = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd2 == -1)
			ft_error("minishell: error while opening file\n");
		else
		{
			dup2(fd2, FD_STDOUT);
			close(fd2);
		}
	}
}

void	ft_redirections(t_list *lst)
{
	int		j;
	char	**cmd;

	j = 0;
	cmd = lst->token->cmd;
	while (cmd[j])
	{
		if (cmd[j][0] == '>')
		{
			if (cmd[j][1] == '>')
				ft_redirection_right_right(cmd, j);
			else
				ft_redirection_right(cmd, j);
		}
		else if (cmd[j][0] == '<')
		{
			if (cmd[j][1] == '<')
				ft_dup_heredocs(lst);
			else
				ft_redirection_left(cmd, j);
		}
		j++;
	}
}

void	ft_exec_redir(t_list **lst, char ***ad_cmd)
{
	t_list	*tmp;

	tmp = *lst;
	*ad_cmd = ft_clean_redirection(tmp->token->cmd);
	ft_redirections(tmp);
}
