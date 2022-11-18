/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:06:57 by mcauchy           #+#    #+#             */
/*   Updated: 2022/11/18 02:10:33 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		hasta_la_vista(0);
	printf("%s\n", pwd);
	free(pwd);
}

void	cd_cmd(char **cmd)
{
	char	*pwd;
	char	*cwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		hasta_la_vista(0);
	if (chdir(cmd[1]) == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n", cmd[1]);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		hasta_la_vista(0);
	search_and_replace_pwd(cwd, pwd);
	free(pwd);
	free(cwd);
}
