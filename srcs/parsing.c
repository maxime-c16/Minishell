/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:03 by mcauchy           #+#    #+#             */
/*   Updated: 2022/08/18 17:49:55 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	insert_env_var(char **token)
{
	dprintf(2, "%s\n ", *token);
	return (1);
}

int	parsing(char *cmd, char **env)
{
	char	**token;

	if (!test_env(env))
		return (0);
	if (!split_env(env))
		return (0);
	if (!cmd)
		hasta_la_vista();
	token = ft_split_parsing(cmd, ' ');
//<<<<<<< HEAD
//	if (!insert_env_var(token))
//		return (0);
//=======
	if (!token)
		hasta_la_vista();
//>>>>>>> da4dae3ca68b978de457d94dc95c0fc8b1d89d5f
	ft_parse_and_insert(token, env);
	free(cmd);
 	return (1);
}
